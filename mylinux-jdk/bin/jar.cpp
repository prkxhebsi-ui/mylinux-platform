#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "jar",
        "jar [OPTION...] [ARCHIVE] [FILES...]");

    if (result >= 0)
        return result;

    std::cerr << "jar: archive engine is not implemented yet\n";
    return 1;
}
