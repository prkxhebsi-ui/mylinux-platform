#include <mylinux/art/interpreter/DexMethodInterpreter.h>

#include <cstdint>
#include <limits>
#include <vector>

namespace art {
namespace interpreter {

namespace {

struct ReturnValue {
    bool returned = false;
    bool has_value = false;
    int32_t value = 0;
};

int32_t SignExtend4(uint32_t value) {
    value &= 0xFU;
    return (value & 8U)
        ? static_cast<int32_t>(value) - 16
        : static_cast<int32_t>(value);
}

int32_t SignExtend16(uint32_t value) {
    value &= 0xFFFFU;
    return (value & 0x8000U)
        ? static_cast<int32_t>(value) - 65536
        : static_cast<int32_t>(value);
}

bool CheckedInt32(int64_t value, int32_t* output) {
    if (value < std::numeric_limits<int32_t>::min() ||
        value > std::numeric_limits<int32_t>::max()) {
        return false;
    }

    *output = static_cast<int32_t>(value);
    return true;
}

class ExecutionEngine {
public:
    ExecutionEngine(
        const DexMethod* methods,
        size_t method_count,
        uint64_t max_steps,
        uint32_t max_depth
    )
        : methods_(methods),
          method_count_(method_count),
          max_steps_(max_steps),
          max_depth_(max_depth) {}

    MethodExecutionResult Run(uint16_t entry_index) {
        MethodExecutionResult result;

        const DexMethod* entry = FindMethod(entry_index);

        if (entry == nullptr) {
            result.error = "entry method not found";
            return result;
        }

        if (entry->input_register_count != 0) {
            result.error = "entry method must not require input registers";
            return result;
        }

        ReturnValue returned;
        if (!ExecuteMethod(*entry, nullptr, 0, 1, &returned)) {
            result.error = error_;
            result.steps = steps_;
            result.calls = calls_;
            return result;
        }

        result.success = true;
        result.returned = returned.returned;
        result.has_value = returned.has_value;
        result.value = returned.value;
        result.steps = steps_;
        result.calls = calls_;
        return result;
    }

private:
    const DexMethod* FindMethod(uint16_t index) const {
        for (size_t i = 0; i < method_count_; ++i) {
            if (methods_[i].method_index == index)
                return &methods_[i];
        }

        return nullptr;
    }

    bool Fail(const std::string& message) {
        error_ = message;
        return false;
    }

    bool ExecuteMethod(
        const DexMethod& method,
        const int32_t* arguments,
        uint32_t argument_count,
        uint32_t depth,
        ReturnValue* returned
    ) {
        if (depth > max_depth_)
            return Fail("maximum method call depth exceeded");

        if (method.instructions == nullptr ||
            method.instruction_count == 0) {
            return Fail("method has no instructions");
        }

        if (method.input_register_count > method.register_count)
            return Fail("method input registers exceed register count");

        if (argument_count != method.input_register_count)
            return Fail("method argument count mismatch");

        if (argument_count != 0 && arguments == nullptr)
            return Fail("missing method arguments");

        std::vector<int32_t> registers(
            method.register_count, 0
        );

        // DEX incoming arguments occupy the last registers.
        const uint32_t input_start =
            method.register_count - method.input_register_count;

        for (uint32_t i = 0; i < argument_count; ++i)
            registers[input_start + i] = arguments[i];

        size_t pc = 0;

        bool pending_result = false;
        bool pending_has_value = false;
        int32_t pending_value = 0;

        while (pc < method.instruction_count) {
            if (steps_ >= max_steps_)
                return Fail("global instruction execution limit reached");

            ++steps_;

            const uint16_t instruction = method.instructions[pc];
            const uint8_t opcode =
                static_cast<uint8_t>(instruction & 0xFFU);

            const uint32_t a8 = (instruction >> 8) & 0xFFU;
            const uint32_t a4 = (instruction >> 8) & 0x0FU;
            const uint32_t b4 = (instruction >> 12) & 0x0FU;

            // A pending invoke result must be consumed immediately
            // by move-result, or it is discarded.
            if (pending_result && opcode != 0x0A) {
                pending_result = false;
                pending_has_value = false;
            }

            switch (opcode) {
                case 0x01: { // move vA, vB
                    if (a4 >= registers.size() ||
                        b4 >= registers.size()) {
                        return Fail("move register out of range");
                    }

                    registers[a4] = registers[b4];
                    ++pc;
                    break;
                }

                case 0x0A: { // move-result vAA
                    if (!pending_result || !pending_has_value)
                        return Fail("move-result without a value-returning invoke");

                    if (a8 >= registers.size())
                        return Fail("move-result register out of range");

                    registers[a8] = pending_value;
                    pending_result = false;
                    pending_has_value = false;
                    ++pc;
                    break;
                }

                case 0x0E: { // return-void
                    returned->returned = true;
                    returned->has_value = false;
                    returned->value = 0;
                    return true;
                }

                case 0x0F: { // return vAA
                    if (a8 >= registers.size())
                        return Fail("return register out of range");

                    returned->returned = true;
                    returned->has_value = true;
                    returned->value = registers[a8];
                    return true;
                }

                case 0x12: { // const/4
                    if (a4 >= registers.size())
                        return Fail("const/4 register out of range");

                    registers[a4] = SignExtend4(b4);
                    ++pc;
                    break;
                }

                case 0x13: { // const/16
                    if (pc + 1 >= method.instruction_count)
                        return Fail("truncated const/16");

                    if (a8 >= registers.size())
                        return Fail("const/16 register out of range");

                    registers[a8] =
                        SignExtend16(method.instructions[pc + 1]);

                    pc += 2;
                    break;
                }

                case 0x90: { // add-int vAA, vBB, vCC
                    if (pc + 1 >= method.instruction_count)
                        return Fail("truncated add-int");

                    const uint32_t b =
                        method.instructions[pc + 1] & 0xFFU;
                    const uint32_t c =
                        method.instructions[pc + 1] >> 8;

                    if (a8 >= registers.size() ||
                        b >= registers.size() ||
                        c >= registers.size()) {
                        return Fail("add-int register out of range");
                    }

                    int32_t value = 0;

                    if (!CheckedInt32(
                            static_cast<int64_t>(registers[b]) +
                            registers[c], &value)) {
                        return Fail("add-int overflow");
                    }

                    registers[a8] = value;
                    pc += 2;
                    break;
                }

                case 0x91: { // sub-int
                    if (pc + 1 >= method.instruction_count)
                        return Fail("truncated sub-int");

                    const uint32_t b =
                        method.instructions[pc + 1] & 0xFFU;
                    const uint32_t c =
                        method.instructions[pc + 1] >> 8;

                    if (a8 >= registers.size() ||
                        b >= registers.size() ||
                        c >= registers.size()) {
                        return Fail("sub-int register out of range");
                    }

                    int32_t value = 0;

                    if (!CheckedInt32(
                            static_cast<int64_t>(registers[b]) -
                            registers[c], &value)) {
                        return Fail("sub-int overflow");
                    }

                    registers[a8] = value;
                    pc += 2;
                    break;
                }

                case 0x71: { // invoke-static {C,D,E,F,G}, method@BBBB
                    if (pc + 2 >= method.instruction_count)
                        return Fail("truncated invoke-static");

                    const uint32_t argument_count =
                        (instruction >> 8) & 0x0FU;

                    const uint32_t fifth_register =
                        (instruction >> 12) & 0x0FU;

                    const uint16_t target_index =
                        method.instructions[pc + 1];

                    const uint16_t packed_registers =
                        method.instructions[pc + 2];

                    if (argument_count > 5)
                        return Fail("invoke-static has more than five arguments");

                    const uint32_t argument_registers[5] = {
                        packed_registers & 0x0FU,
                        (packed_registers >> 4) & 0x0FU,
                        (packed_registers >> 8) & 0x0FU,
                        (packed_registers >> 12) & 0x0FU,
                        fifth_register
                    };

                    int32_t arguments[5] = {};

                    for (uint32_t i = 0; i < argument_count; ++i) {
                        const uint32_t reg = argument_registers[i];

                        if (reg >= registers.size())
                            return Fail("invoke-static argument register out of range");

                        arguments[i] = registers[reg];
                    }

                    const DexMethod* target = FindMethod(target_index);

                    if (target == nullptr)
                        return Fail("invoke-static target method not found");

                    ReturnValue child_result{};

                    ++calls_;

                    if (!ExecuteMethod(
                            *target,
                            arguments,
                            argument_count,
                            depth + 1,
                            &child_result)) {
                        return false;
                    }

                    if (!child_result.returned)
                        return Fail("called method did not return");

                    pending_result = true;
                    pending_has_value = child_result.has_value;
                    pending_value = child_result.value;

                    pc += 3;
                    break;
                }

                default:
                    return Fail(
                        "unsupported DEX opcode " +
                        std::to_string(opcode)
                    );
            }
        }

        return Fail("method ended without return instruction");
    }

    const DexMethod* methods_;
    size_t method_count_;
    uint64_t max_steps_;
    uint32_t max_depth_;

    uint64_t steps_ = 0;
    uint32_t calls_ = 0;
    std::string error_;
};

} // namespace

MethodExecutionResult DexMethodInterpreter::Execute(
    const DexMethod* methods,
    size_t method_count,
    uint16_t entry_method_index,
    uint64_t max_steps,
    uint32_t max_call_depth
) const {
    if (methods == nullptr || method_count == 0) {
        MethodExecutionResult result;
        result.error = "empty method table";
        return result;
    }

    if (max_steps == 0 || max_call_depth == 0) {
        MethodExecutionResult result;
        result.error = "execution limits must be nonzero";
        return result;
    }

    ExecutionEngine engine(
        methods,
        method_count,
        max_steps,
        max_call_depth
    );

    return engine.Run(entry_method_index);
}

} // namespace interpreter
} // namespace art
