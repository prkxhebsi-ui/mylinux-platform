#include "SocketAddress.h"

#include <cerrno>
#include <cstring>

namespace mylinux {
namespace socket {

bool SocketAddress::IsValidPath(const std::string& path) {
    if (path.empty()) {
        return false;
    }

    if (path[0] != '/') {
        return false;
    }

    if (path.size() >= sizeof(sockaddr_un::sun_path)) {
        return false;
    }

    return true;
}

SocketResult SocketAddress::Build(
    const std::string& path,
    sockaddr_un* address,
    socklen_t* address_length
) {
    if (address == nullptr || address_length == nullptr) {
        return SocketResult(
            SocketStatus::INVALID_ARGUMENT,
            EINVAL
        );
    }

    if (!IsValidPath(path)) {
        return SocketResult(
            SocketStatus::INVALID_PATH,
            ENAMETOOLONG
        );
    }

    std::memset(address, 0, sizeof(*address));
    address->sun_family = AF_UNIX;

    std::memcpy(
        address->sun_path,
        path.c_str(),
        path.size() + 1
    );

    *address_length = static_cast<socklen_t>(
        offsetof(sockaddr_un, sun_path) +
        path.size() + 1
    );

    return SocketResult();
}

} // namespace socket
} // namespace mylinux
