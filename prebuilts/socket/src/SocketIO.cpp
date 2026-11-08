#include "SocketIO.h"

#include <cerrno>
#include <sys/socket.h>

namespace mylinux {
namespace socket {

SocketResult SocketIO::SendAll(
    SocketNativeHandle fd,
    const void* data,
    size_t size,
    size_t* sent
) {
    if (sent) *sent = 0;

    if (fd < 0 || (data == nullptr && size != 0)) {
        return SocketResult(
            SocketStatus::INVALID_ARGUMENT,
            EINVAL
        );
    }

    const char* bytes = static_cast<const char*>(data);
    size_t offset = 0;

    while (offset < size) {
#ifdef MSG_NOSIGNAL
        ssize_t result = send(
            fd,
            bytes + offset,
            size - offset,
            MSG_NOSIGNAL
        );
#else
        ssize_t result = send(
            fd,
            bytes + offset,
            size - offset,
            0
        );
#endif

        if (result < 0) {
            if (errno == EINTR) continue;

            if (sent) *sent = offset;

            return SocketResult(
                SocketStatus::SEND_FAILED,
                errno
            );
        }

        if (result == 0) {
            if (sent) *sent = offset;

            return SocketResult(
                SocketStatus::CONNECTION_CLOSED,
                0
            );
        }

        offset += static_cast<size_t>(result);
    }

    if (sent) *sent = offset;
    return SocketResult();
}

SocketResult SocketIO::ReceiveExact(
    SocketNativeHandle fd,
    void* buffer,
    size_t size,
    size_t* received
) {
    if (received) *received = 0;

    if (fd < 0 || (buffer == nullptr && size != 0)) {
        return SocketResult(
            SocketStatus::INVALID_ARGUMENT,
            EINVAL
        );
    }

    char* bytes = static_cast<char*>(buffer);
    size_t offset = 0;

    while (offset < size) {
        ssize_t result = recv(
            fd,
            bytes + offset,
            size - offset,
            0
        );

        if (result < 0) {
            if (errno == EINTR) continue;

            if (received) *received = offset;

            return SocketResult(
                SocketStatus::RECEIVE_FAILED,
                errno
            );
        }

        if (result == 0) {
            if (received) *received = offset;

            return SocketResult(
                SocketStatus::CONNECTION_CLOSED,
                0
            );
        }

        offset += static_cast<size_t>(result);
    }

    if (received) *received = offset;
    return SocketResult();
}

SocketResult SocketIO::SendString(
    SocketNativeHandle fd,
    const std::string& message
) {
    return SendAll(
        fd,
        message.data(),
        message.size(),
        nullptr
    );
}

} // namespace socket
} // namespace mylinux
