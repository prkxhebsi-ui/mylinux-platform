#ifndef MYLINUX_SOCKET_FD_H
#define MYLINUX_SOCKET_FD_H

#include "SocketTypes.h"

namespace mylinux {
namespace socket {

class SocketFD {
public:
    SocketFD();
    explicit SocketFD(SocketNativeHandle fd);

    ~SocketFD();

    SocketFD(const SocketFD&) = delete;
    SocketFD& operator=(const SocketFD&) = delete;

    SocketFD(SocketFD&& other) noexcept;
    SocketFD& operator=(SocketFD&& other) noexcept;

    bool IsValid() const;
    SocketNativeHandle Get() const;

    SocketNativeHandle Release();
    void Reset(SocketNativeHandle fd = INVALID_SOCKET_HANDLE);

private:
    SocketNativeHandle fd_;
};

} // namespace socket
} // namespace mylinux

#endif
