#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "java",
        "java [options] <mainclass> [arguments...]");

    if (result >= 0)
        return result;

    if (argc < 2) {
        std::cerr << "Usage: java <mainclass>\n";
        return 2;
    }

    std::cerr << "java: MyLinux virtual machine is not implemented yet\n";
    std::cerr << "Requested entry: " << argv[argc - 1] << '\n';
    return 1;
}
