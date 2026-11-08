#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "jshell",
        "jshell [options]");

    if (result >= 0)
        return result;

    std::cerr << "jshell: interactive Java evaluator is not implemented yet\n";
    return 1;
}
