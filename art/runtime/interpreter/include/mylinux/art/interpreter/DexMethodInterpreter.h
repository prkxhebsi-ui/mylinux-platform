#ifndef MYLINUX_ART_INTERPRETER_DEX_METHOD_INTERPRETER_H
#define MYLINUX_ART_INTERPRETER_DEX_METHOD_INTERPRETER_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace art {
namespace interpreter {

struct DexMethod {
    uint16_t method_index = 0;
    uint16_t register_count = 0;
    uint16_t input_register_count = 0;
    const uint16_t* instructions = nullptr;
    size_t instruction_count = 0;
};

struct MethodExecutionResult {
    bool success = false;
    bool returned = false;
    bool has_value = false;
    int32_t value = 0;
    uint64_t steps = 0;
    uint32_t calls = 0;
    std::string error;
};

class DexMethodInterpreter {
public:
    MethodExecutionResult Execute(
        const DexMethod* methods,
        size_t method_count,
        uint16_t entry_method_index,
        uint64_t max_steps = 100000,
        uint32_t max_call_depth = 64
    ) const;
};

} // namespace interpreter
} // namespace art

#endif
