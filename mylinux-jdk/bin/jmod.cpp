#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "jmod",
        "jmod (create|extract|list|describe) <jmod-file>");

    if (result >= 0)
        return result;

    std::cerr << "jmod: module archive engine is not implemented yet\n";
    return 1;
}
