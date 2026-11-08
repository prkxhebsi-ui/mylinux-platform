#include "SocketServer.h"

#include <cerrno>
#include <cstring>

#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

namespace mylinux {
namespace socket {

SocketServer::SocketServer()
    : listening_(false),
      path_device_(0),
      path_inode_(0),
      owns_path_(false) {
}

SocketServer::~SocketServer() {
    Stop();
}

SocketResult SocketServer::Start(
    const std::string& path,
    int backlog
) {
    if (listening_) {
        return SocketResult(
            SocketStatus::ALREADY_RUNNING,
            EALREADY
        );
    }

    if (backlog <= 0) {
        return SocketResult(
            SocketStatus::INVALID_ARGUMENT,
            EINVAL
        );
    }

    sockaddr_un address;
    socklen_t address_length = 0;

    SocketResult address_result = SocketAddress::Build(
        path,
        &address,
        &address_length
    );

    if (!address_result.Success()) {
        return address_result;
    }

    SocketFD fd(::socket(AF_UNIX, SOCK_STREAM, 0));

    if (!fd.IsValid()) {
        return SocketResult(
            SocketStatus::CREATE_FAILED,
            errno
        );
    }

    if (::bind(
        fd.Get(),
        reinterpret_cast<sockaddr*>(&address),
        address_length
    ) < 0) {
        return SocketResult(
            SocketStatus::BIND_FAILED,
            errno
        );
    }

    // Restrict the socket to its owning user.
    if (::chmod(path.c_str(), 0600) < 0) {
        int error = errno;
        ::unlink(path.c_str());

        return SocketResult(
            SocketStatus::BIND_FAILED,
            error
        );
    }

    struct stat info;

    if (::lstat(path.c_str(), &info) < 0 ||
        !S_ISSOCK(info.st_mode)) {
        int error = errno ? errno : EINVAL;
        ::unlink(path.c_str());

        return SocketResult(
            SocketStatus::BIND_FAILED,
            error
        );
    }

    path_ = path;
    path_device_ = info.st_dev;
    path_inode_ = info.st_ino;
    owns_path_ = true;

    if (::listen(fd.Get(), backlog) < 0) {
        int error = errno;
        RemoveOwnedPath();

        return SocketResult(
            SocketStatus::LISTEN_FAILED,
            error
        );
    }

    server_fd_ = std::move(fd);
    listening_ = true;

    return SocketResult();
}

SocketResult SocketServer::Accept(SocketFD* client) {
    if (client == nullptr || !listening_) {
        return SocketResult(
            SocketStatus::INVALID_ARGUMENT,
            EINVAL
        );
    }

    for (;;) {
        int fd = ::accept(server_fd_.Get(), nullptr, nullptr);

        if (fd >= 0) {
            client->Reset(fd);
            statistics_.connections_accepted++;
            return SocketResult();
        }

        if (errno == EINTR) continue;

        statistics_.connections_failed++;

        return SocketResult(
            SocketStatus::ACCEPT_FAILED,
            errno
        );
    }
}

void SocketServer::RemoveOwnedPath() {
    if (!owns_path_) return;

    struct stat info;

    if (::lstat(path_.c_str(), &info) == 0 &&
        S_ISSOCK(info.st_mode) &&
        info.st_dev == path_device_ &&
        info.st_ino == path_inode_) {
        ::unlink(path_.c_str());
    }

    owns_path_ = false;
}

void SocketServer::Stop() {
    listening_ = false;
    server_fd_.Reset();
    RemoveOwnedPath();
}

bool SocketServer::IsListening() const {
    return listening_;
}

const std::string& SocketServer::GetPath() const {
    return path_;
}

SocketStatistics SocketServer::GetStatistics() const {
    return statistics_;
}

} // namespace socket
} // namespace mylinux
