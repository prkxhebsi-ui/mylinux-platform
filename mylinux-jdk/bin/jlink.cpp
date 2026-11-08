#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "jlink",
        "jlink [options] --module-path <path> --add-modules <modules>");

    if (result >= 0)
        return result;

    std::cerr << "jlink: runtime image builder is not implemented yet\n";
    return 1;
}
