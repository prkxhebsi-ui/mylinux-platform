#include <mylinux/art/interpreter/DexInterpreter.h>

#include <cstdint>
#include <iostream>

int main() {
    using art::interpreter::DexInterpreter;

    // DEX instructions:
    //
    // const/4 v0, 6
    // const/4 v1, 7
    // add-int v2, v0, v1
    // return v2
    //
    // DEX instructions are stored as 16-bit code units.

    const uint16_t program[] = {
        0x6012,
        0x7112,
        0x0290,
        0x0100,
        0x020F
    };

    DexInterpreter interpreter;

    const auto result = interpreter.Execute(
        program,
        sizeof(program) / sizeof(program[0]),
        3
    );

    if (!result.success) {
        std::cerr << "Interpreter error: "
                  << result.error << '\n';
        return 1;
    }

    if (!result.returned ||
        !result.has_value ||
        result.value != 13) {
        std::cerr << "Test failed: expected return value 13\n";
        return 1;
    }

    std::cout << "MyLinux DEX Interpreter\n";
    std::cout << "Execution successful.\n";
    std::cout << "Result: " << result.value << '\n';
    std::cout << "Instructions executed: "
              << result.steps << '\n';
    std::cout << "TEST PASSED\n";

    return 0;
}
