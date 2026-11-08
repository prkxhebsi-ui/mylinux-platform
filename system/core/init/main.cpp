#include "init.h"

int main(int argc, char** argv) {
    mylinux::init::InitOptions options;

    if (!mylinux::init::parse_arguments(argc, argv, options)) {
        return 2;
    }

    // Version information is not permission to initialize.
    if (options.show_version) {
        mylinux::init::print_version();
        return 0;
    }

    if (!mylinux::init::initialize(options)) {
        return 1;
    }

    return 0;
}
