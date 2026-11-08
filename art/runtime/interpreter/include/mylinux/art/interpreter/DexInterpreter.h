#ifndef MYLINUX_ART_INTERPRETER_DEX_INTERPRETER_H
#define MYLINUX_ART_INTERPRETER_DEX_INTERPRETER_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace art {
namespace interpreter {

struct ExecutionResult {
    bool success = false;
    bool returned = false;
    bool has_value = false;

    int32_t value = 0;
    uint64_t steps = 0;

    std::string error;
};

class DexInterpreter {
public:
    ExecutionResult Execute(
        const uint16_t* instructions,
        size_t instruction_count,
        uint16_t register_count,
        uint64_t max_steps = 100000
    ) const;
};

} // namespace interpreter
} // namespace art

#endif
