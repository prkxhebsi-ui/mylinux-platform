#include "SocketFD.h"

#include <unistd.h>
#include <fcntl.h>

namespace mylinux {
namespace socket {

SocketFD::SocketFD()
    : fd_(INVALID_SOCKET_HANDLE) {
}

SocketFD::SocketFD(SocketNativeHandle fd)
    : fd_(fd) {
    if (fd_ >= 0) {
        int flags = fcntl(fd_, F_GETFD);
        if (flags >= 0) {
            fcntl(fd_, F_SETFD, flags | FD_CLOEXEC);
        }
    }
}

SocketFD::~SocketFD() {
    Reset();
}

SocketFD::SocketFD(SocketFD&& other) noexcept
    : fd_(other.Release()) {
}

SocketFD& SocketFD::operator=(SocketFD&& other) noexcept {
    if (this != &other) {
        Reset(other.Release());
    }
    return *this;
}

bool SocketFD::IsValid() const {
    return fd_ >= 0;
}

SocketNativeHandle SocketFD::Get() const {
    return fd_;
}

SocketNativeHandle SocketFD::Release() {
    SocketNativeHandle result = fd_;
    fd_ = INVALID_SOCKET_HANDLE;
    return result;
}

void SocketFD::Reset(SocketNativeHandle fd) {
    if (fd_ >= 0) {
        close(fd_);
    }
    fd_ = fd;
}

} // namespace socket
} // namespace mylinux
