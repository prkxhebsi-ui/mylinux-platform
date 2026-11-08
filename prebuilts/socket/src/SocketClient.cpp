#include "SocketClient.h"

#include <cerrno>
#include <sys/socket.h>

namespace mylinux {
namespace socket {

SocketClient::SocketClient() {
}

SocketResult SocketClient::Connect(const std::string& path) {
    if (fd_.IsValid()) {
        return SocketResult(
            SocketStatus::ALREADY_RUNNING,
            EALREADY
        );
    }

    sockaddr_un address;
    socklen_t address_length = 0;

    SocketResult result = SocketAddress::Build(
        path,
        &address,
        &address_length
    );

    if (!result.Success()) {
        return result;
    }

    SocketFD candidate(::socket(AF_UNIX, SOCK_STREAM, 0));

    if (!candidate.IsValid()) {
        return SocketResult(
            SocketStatus::CREATE_FAILED,
            errno
        );
    }

    if (::connect(
        candidate.Get(),
        reinterpret_cast<sockaddr*>(&address),
        address_length
    ) < 0) {
        return SocketResult(
            SocketStatus::CONNECT_FAILED,
            errno
        );
    }

    fd_ = std::move(candidate);
    return SocketResult();
}

void SocketClient::Disconnect() {
    fd_.Reset();
}

bool SocketClient::IsConnected() const {
    return fd_.IsValid();
}

SocketNativeHandle SocketClient::GetHandle() const {
    return fd_.Get();
}

} // namespace socket
} // namespace mylinux
