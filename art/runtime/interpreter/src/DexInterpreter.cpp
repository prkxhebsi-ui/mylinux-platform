#include <mylinux/art/interpreter/DexInterpreter.h>

#include <cstdint>
#include <limits>
#include <vector>

namespace art {
namespace interpreter {

namespace {

int32_t SignExtend4(uint32_t value) {
    value &= 0xFU;
    return (value & 8U)
        ? static_cast<int32_t>(value) - 16
        : static_cast<int32_t>(value);
}

int32_t SignExtend8(uint32_t value) {
    value &= 0xFFU;
    return (value & 0x80U)
        ? static_cast<int32_t>(value) - 256
        : static_cast<int32_t>(value);
}

int32_t SignExtend16(uint32_t value) {
    value &= 0xFFFFU;
    return (value & 0x8000U)
        ? static_cast<int32_t>(value) - 65536
        : static_cast<int32_t>(value);
}

int32_t ReadSigned32(
    const uint16_t* instructions,
    size_t pc
) {
    const uint32_t value =
        static_cast<uint32_t>(instructions[pc + 1]) |
        (static_cast<uint32_t>(instructions[pc + 2]) << 16);

    return static_cast<int32_t>(value);
}

bool CheckedResult(
    int64_t value,
    int32_t* output
) {
    if (value < std::numeric_limits<int32_t>::min() ||
        value > std::numeric_limits<int32_t>::max()) {
        return false;
    }

    *output = static_cast<int32_t>(value);
    return true;
}

} // namespace

ExecutionResult DexInterpreter::Execute(
    const uint16_t* instructions,
    size_t instruction_count,
    uint16_t register_count,
    uint64_t max_steps
) const {
    ExecutionResult result;

    if (instructions == nullptr || instruction_count == 0) {
        result.error = "empty instruction stream";
        return result;
    }

    if (register_count == 0) {
        result.error = "register file is empty";
        return result;
    }

    if (max_steps == 0) {
        result.error = "instruction limit is zero";
        return result;
    }

    std::vector<int32_t> registers(register_count, 0);

    size_t pc = 0;

    auto valid_register = [&](uint32_t index) {
        return index < registers.size();
    };

    auto branch = [&](int32_t relative_offset) -> bool {
        const int64_t target =
            static_cast<int64_t>(pc) + relative_offset;

        if (target < 0 ||
            target >= static_cast<int64_t>(instruction_count)) {
            result.error = "branch target outside instruction stream";
            return false;
        }

        pc = static_cast<size_t>(target);
        return true;
    };

    while (pc < instruction_count) {
        if (result.steps >= max_steps) {
            result.error = "instruction execution limit reached";
            return result;
        }

        ++result.steps;

        const uint16_t instruction = instructions[pc];
        const uint8_t opcode =
            static_cast<uint8_t>(instruction & 0xFFU);

        const uint32_t a8 = (instruction >> 8) & 0xFFU;
        const uint32_t a4 = (instruction >> 8) & 0x0FU;
        const uint32_t b4 = (instruction >> 12) & 0x0FU;

        switch (opcode) {
            case 0x01: { // move vA, vB (12x)
                if (!valid_register(a4) ||
                    !valid_register(b4)) {
                    result.error = "move register index out of range";
                    return result;
                }

                registers[a4] = registers[b4];
                ++pc;
                break;
            }

            case 0x0E: { // return-void
                result.success = true;
                result.returned = true;
                result.has_value = false;
                return result;
            }

            case 0x0F: { // return vA
                if (!valid_register(a8)) {
                    result.error = "return register out of range";
                    return result;
                }

                result.success = true;
                result.returned = true;
                result.has_value = true;
                result.value = registers[a8];
                return result;
            }

            case 0x12: { // const/4 vA, #+B
                if (!valid_register(a4)) {
                    result.error = "const/4 register out of range";
                    return result;
                }

                registers[a4] = SignExtend4(b4);
                ++pc;
                break;
            }

            case 0x13: { // const/16 vAA, #+BBBB
                if (pc + 1 >= instruction_count) {
                    result.error = "truncated const/16 instruction";
                    return result;
                }

                if (!valid_register(a8)) {
                    result.error = "const/16 register out of range";
                    return result;
                }

                registers[a8] =
                    SignExtend16(instructions[pc + 1]);

                pc += 2;
                break;
            }

            case 0x14: { // const vAA, #+BBBBBBBB
                if (pc + 2 >= instruction_count) {
                    result.error = "truncated const instruction";
                    return result;
                }

                if (!valid_register(a8)) {
                    result.error = "const register out of range";
                    return result;
                }

                registers[a8] =
                    ReadSigned32(instructions, pc);

                pc += 3;
                break;
            }

            case 0x28: { // goto +AA (10t)
                const int32_t offset =
                    SignExtend8(instruction >> 8);

                if (!branch(offset))
                    return result;

                break;
            }

            case 0x38: // if-eqz vAA, +BBBB
            case 0x39: { // if-nez vAA, +BBBB
                if (pc + 1 >= instruction_count) {
                    result.error = "truncated conditional branch";
                    return result;
                }

                if (!valid_register(a8)) {
                    result.error = "branch register out of range";
                    return result;
                }

                const int32_t offset =
                    SignExtend16(instructions[pc + 1]);

                const bool is_zero = registers[a8] == 0;
                const bool take_branch =
                    opcode == 0x38 ? is_zero : !is_zero;

                if (take_branch) {
                    if (!branch(offset))
                        return result;
                } else {
                    pc += 2;
                }

                break;
            }

            case 0x90: // add-int vAA, vBB, vCC
            case 0x91: // sub-int
            case 0x92: // mul-int
            case 0x93: { // div-int
                if (pc + 1 >= instruction_count) {
                    result.error = "truncated arithmetic instruction";
                    return result;
                }

                const uint32_t b =
                    instructions[pc + 1] & 0xFFU;

                const uint32_t c =
                    (instructions[pc + 1] >> 8) & 0xFFU;

                if (!valid_register(a8) ||
                    !valid_register(b) ||
                    !valid_register(c)) {
                    result.error = "arithmetic register out of range";
                    return result;
                }

                const int64_t left = registers[b];
                const int64_t right = registers[c];

                int32_t value = 0;

                if (opcode == 0x90) {
                    if (!CheckedResult(
                            left + right, &value)) {
                        result.error = "integer addition overflow";
                        return result;
                    }
                } else if (opcode == 0x91) {
                    if (!CheckedResult(
                            left - right, &value)) {
                        result.error = "integer subtraction overflow";
                        return result;
                    }
                } else if (opcode == 0x92) {
                    if (!CheckedResult(
                            left * right, &value)) {
                        result.error = "integer multiplication overflow";
                        return result;
                    }
                } else {
                    if (right == 0) {
                        result.error = "division by zero";
                        return result;
                    }

                    if (left == std::numeric_limits<int32_t>::min() &&
                        right == -1) {
                        result.error = "integer division overflow";
                        return result;
                    }

                    value = static_cast<int32_t>(left / right);
                }

                registers[a8] = value;
                pc += 2;
                break;
            }

            default:
                result.error =
                    "unsupported DEX opcode: " +
                    std::to_string(opcode);
                return result;
        }
    }

    result.error = "instruction stream ended without return";
    return result;
}

} // namespace interpreter
} // namespace art
