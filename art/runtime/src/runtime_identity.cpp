#include <cstdio>
#include "mylinux/art/RuntimeIdentity.h"

int main() {
    using mylinux::art::RuntimeIdentity;

    std::printf("%s\n", RuntimeIdentity::name());
    std::printf("Implementation: %s\n",
                RuntimeIdentity::implementation());
    std::printf("Vendor: %s\n", RuntimeIdentity::vendor());
    std::printf("Version: %s\n", RuntimeIdentity::version());
    std::printf("Architecture: %s\n",
                RuntimeIdentity::architecture());
    std::printf("Execution mode: %s\n",
                RuntimeIdentity::executionMode());

    return 0;
}
