#ifndef MYLINUX_SOCKET_ADDRESS_H
#define MYLINUX_SOCKET_ADDRESS_H

#include "SocketTypes.h"

#include <sys/socket.h>
#include <sys/un.h>

namespace mylinux {
namespace socket {

class SocketAddress {
public:
    static SocketResult Build(
        const std::string& path,
        sockaddr_un* address,
        socklen_t* address_length
    );

    static bool IsValidPath(const std::string& path);
};

} // namespace socket
} // namespace mylinux

#endif
