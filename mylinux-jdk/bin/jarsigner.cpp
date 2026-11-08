#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "jarsigner",
        "jarsigner [options] jar-file alias");

    if (result >= 0)
        return result;

    std::cerr << "jarsigner: signing and verification engine "
                 "is not implemented yet\n";
    return 1;
}
