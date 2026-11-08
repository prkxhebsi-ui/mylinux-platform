#include "tool_common.h"

int main(int argc, char **argv) {
    int result = common_options(
        argc, argv, "keytool",
        "keytool -genkeypair|-importcert|-list [options]");

    if (result >= 0)
        return result;

    std::cerr << "keytool: cryptographic keystore engine "
                 "is not implemented yet\n";
    return 1;
}
