#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "jdeps",
        "jdeps [options] <path>");

    if (result >= 0)
        return result;

    std::cerr << "jdeps: dependency analyzer is not implemented yet\n";
    return 1;
}
