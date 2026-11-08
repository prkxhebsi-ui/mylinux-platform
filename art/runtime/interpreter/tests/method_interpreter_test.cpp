#include <mylinux/art/interpreter/DexMethodInterpreter.h>

#include <cstdint>
#include <iostream>

int main() {
    using art::interpreter::DexMethod;
    using art::interpreter::DexMethodInterpreter;

    // Method 0: main()
    //
    // const/4 v0, 6
    // const/4 v1, 7
    // invoke-static {v0, v1}, method@1
    // move-result v2
    // return v2

    const uint16_t main_code[] = {
        0x6012,
        0x7112,
        0x0271,
        0x0001,
        0x0010,
        0x020A,
        0x020F
    };

    // Method 1: add(int, int)
    //
    // registers_size = 3
    // ins_size = 2
    // Incoming arguments are v1 and v2.
    //
    // add-int v0, v1, v2
    // return v0

    const uint16_t add_code[] = {
        0x0090,
        0x0201,
        0x000F
    };

    const DexMethod methods[] = {
        {
            0,
            3,
            0,
            main_code,
            sizeof(main_code) / sizeof(main_code[0])
        },
        {
            1,
            3,
            2,
            add_code,
            sizeof(add_code) / sizeof(add_code[0])
        }
    };

    DexMethodInterpreter interpreter;

    const auto result = interpreter.Execute(
        methods,
        sizeof(methods) / sizeof(methods[0]),
        0
    );

    if (!result.success) {
        std::cerr << "Execution error: "
                  << result.error << '\n';
        return 1;
    }

    if (!result.returned ||
        !result.has_value ||
        result.value != 13 ||
        result.calls != 1) {
        std::cerr << "Test failed: expected 13 from one method call\n";
        return 1;
    }

    std::cout << "MyLinux DEX Method Interpreter\n";
    std::cout << "Execution successful.\n";
    std::cout << "Returned value: " << result.value << '\n';
    std::cout << "Method calls: " << result.calls << '\n';
    std::cout << "Instructions executed: " << result.steps << '\n';
    std::cout << "TEST PASSED\n";

    return 0;
}
