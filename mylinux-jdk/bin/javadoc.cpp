#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "javadoc",
        "javadoc [options] <packages> <source files>");

    if (result >= 0)
        return result;

    std::cerr << "javadoc: documentation generator is not implemented yet\n";
    return 1;
}
