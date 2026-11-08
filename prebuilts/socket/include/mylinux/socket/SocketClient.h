#ifndef MYLINUX_SOCKET_CLIENT_H
#define MYLINUX_SOCKET_CLIENT_H

#include "SocketFD.h"
#include "SocketAddress.h"

namespace mylinux {
namespace socket {

class SocketClient {
public:
    SocketClient();

    SocketResult Connect(const std::string& path);
    void Disconnect();

    bool IsConnected() const;
    SocketNativeHandle GetHandle() const;

private:
    SocketFD fd_;
};

} // namespace socket
} // namespace mylinux

#endif
