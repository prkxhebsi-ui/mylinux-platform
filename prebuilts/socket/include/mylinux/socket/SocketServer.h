#ifndef MYLINUX_SOCKET_SERVER_H
#define MYLINUX_SOCKET_SERVER_H

#include "SocketFD.h"
#include "SocketAddress.h"

#include <sys/types.h>

namespace mylinux {
namespace socket {

class SocketServer {
public:
    SocketServer();
    ~SocketServer();

    SocketServer(const SocketServer&) = delete;
    SocketServer& operator=(const SocketServer&) = delete;

    SocketResult Start(
        const std::string& path,
        int backlog = SOCKET_DEFAULT_BACKLOG
    );

    SocketResult Accept(SocketFD* client);

    void Stop();

    bool IsListening() const;
    const std::string& GetPath() const;

    SocketStatistics GetStatistics() const;

private:
    SocketFD server_fd_;
    std::string path_;
    bool listening_;

    dev_t path_device_;
    ino_t path_inode_;
    bool owns_path_;

    SocketStatistics statistics_;

    void RemoveOwnedPath();
};

} // namespace socket
} // namespace mylinux

#endif
