#include "zygote_socket.h"

#include <cerrno>
#include <cstdio>

int main() {
    int serverFd =
        mylinux::zygote::getInheritedServerSocket("zygote_secondary");

    if (serverFd < 0) {
        std::fprintf(
            stderr,
            "zygote_secondary: inherited socket unavailable: errno=%d\n",
            errno
        );
        return 1;
    }

    std::printf(
        "zygote_secondary: inherited listening socket fd=%d\n",
        serverFd
    );

    // The actual Android Zygote runtime and command loop
    // must be integrated here. Do not create a second socket.

    return 0;
}
