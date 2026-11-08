#include "zygote_socket.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstddef>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace mylinux {
namespace zygote {

int getInheritedServerSocket(const char* socketName) {
    if (socketName == nullptr || socketName[0] == '\0') {
        errno = EINVAL;
        return -1;
    }

    char environmentName[128];

    int length = snprintf(
        environmentName,
        sizeof(environmentName),
        "ANDROID_SOCKET_%s",
        socketName
    );

    if (length < 0 ||
        static_cast<size_t>(length) >= sizeof(environmentName)) {
        errno = ENAMETOOLONG;
        return -1;
    }

    const char* value = getenv(environmentName);

    if (value == nullptr || value[0] == '\0') {
        errno = ENOENT;
        return -1;
    }

    char* end = nullptr;
    errno = 0;

    long descriptor = strtol(value, &end, 10);

    if (errno != 0 || end == value || *end != '\0' ||
        descriptor < 0 || descriptor > 0x7fffffffL) {
        errno = EINVAL;
        return -1;
    }

    int fd = static_cast<int>(descriptor);

    int socketType = 0;
    socklen_t typeLength = sizeof(socketType);

    if (getsockopt(
            fd,
            SOL_SOCKET,
            SO_TYPE,
            &socketType,
            &typeLength
        ) != 0) {
        return -1;
    }

    if (socketType != SOCK_STREAM) {
        errno = EPROTOTYPE;
        return -1;
    }

    sockaddr_un address {};
    socklen_t addressLength = sizeof(address);

    if (getsockname(
            fd,
            reinterpret_cast<sockaddr*>(&address),
            &addressLength
        ) != 0) {
        return -1;
    }

    if (address.sun_family != AF_UNIX) {
        errno = EAFNOSUPPORT;
        return -1;
    }

    int accepting = 0;
    socklen_t acceptingLength = sizeof(accepting);

    if (getsockopt(
            fd,
            SOL_SOCKET,
            SO_ACCEPTCONN,
            &accepting,
            &acceptingLength
        ) != 0) {
        return -1;
    }

    if (accepting != 1) {
        errno = EINVAL;
        return -1;
    }

    return fd;
}

} // namespace zygote
} // namespace mylinux
