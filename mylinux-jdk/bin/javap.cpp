#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "javap",
        "javap [options] class");

    if (result >= 0)
        return result;

    std::cerr << "javap: class-file inspector is not implemented yet\n";
    return 1;
}
