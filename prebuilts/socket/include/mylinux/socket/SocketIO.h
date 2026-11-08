#ifndef MYLINUX_SOCKET_IO_H
#define MYLINUX_SOCKET_IO_H

#include "SocketTypes.h"

namespace mylinux {
namespace socket {

class SocketIO {
public:
    static SocketResult SendAll(
        SocketNativeHandle fd,
        const void* data,
        size_t size,
        size_t* sent
    );

    static SocketResult ReceiveExact(
        SocketNativeHandle fd,
        void* buffer,
        size_t size,
        size_t* received
    );

    static SocketResult SendString(
        SocketNativeHandle fd,
        const std::string& message
    );
};

} // namespace socket
} // namespace mylinux

#endif
