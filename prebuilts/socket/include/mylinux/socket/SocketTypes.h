#ifndef MYLINUX_SOCKET_TYPES_H
#define MYLINUX_SOCKET_TYPES_H
#include "SocketPlatform.h"

#include <cstddef>
#include <cstdint>
#include <string>

namespace mylinux {
namespace socket {

typedef int SocketNativeHandle;
typedef uint32_t SocketId;
typedef uint64_t SocketBytes;
typedef uint64_t SocketMessageId;

static const SocketNativeHandle INVALID_SOCKET_HANDLE = -1;
static const size_t SOCKET_MAX_PATH = 107;
static const size_t SOCKET_DEFAULT_BACKLOG = 16;

enum class SocketStatus : uint32_t {
    OK = 0,
    INVALID_ARGUMENT,
    INVALID_PATH,
    CREATE_FAILED,
    BIND_FAILED,
    LISTEN_FAILED,
    ACCEPT_FAILED,
    CONNECT_FAILED,
    SEND_FAILED,
    RECEIVE_FAILED,
    CONNECTION_CLOSED,
    ALREADY_RUNNING,
    OUT_OF_MEMORY
};

enum class SocketKind : uint32_t {
    STREAM = 1,
    DATAGRAM = 2
};

enum class SocketState : uint32_t {
    CREATED,
    BOUND,
    LISTENING,
    CONNECTED,
    CLOSED,
    ERROR
};

struct SocketResult {
    SocketStatus status;
    int system_error;

    SocketResult(
        SocketStatus s = SocketStatus::OK,
        int e = 0
    ) : status(s), system_error(e) {}

    bool Success() const {
        return status == SocketStatus::OK;
    }
};

struct SocketEndpoint {
    std::string path;
    SocketKind kind;
};

struct SocketStatistics {
    SocketBytes bytes_sent = 0;
    SocketBytes bytes_received = 0;
    uint64_t connections_accepted = 0;
    uint64_t connections_failed = 0;
};

} // namespace socket
} // namespace mylinux

#endif
