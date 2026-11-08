#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "javac",
        "javac [options] <source files>");

    if (result >= 0)
        return result;

    if (argc < 2) {
        std::cerr << "javac: no source files specified\n";
        return 2;
    }

    std::cerr << "javac: MyLinux Java compiler backend is not implemented yet\n";
    return 1;
}
