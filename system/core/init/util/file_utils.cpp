#include "file_utils.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

namespace mylinux {
namespace init {

bool PathExists(const std::string& path) {
    struct stat info {};
    return stat(path.c_str(), &info) == 0;
}

bool IsDirectory(const std::string& path) {
    struct stat info {};

    if (stat(path.c_str(), &info) != 0) {
        return false;
    }

    return S_ISDIR(info.st_mode);
}

bool ReadFile(
    const std::string& path,
    std::string* output
) {
    if (output == nullptr) {
        errno = EINVAL;
        return false;
    }

    FILE* file = std::fopen(path.c_str(), "rb");

    if (file == nullptr) {
        return false;
    }

    output->clear();

    char buffer[4096];
    size_t count;

    while ((count = std::fread(buffer, 1, sizeof(buffer), file)) > 0) {
        output->append(buffer, count);
    }

    bool success = !std::ferror(file);

    int saved_errno = errno;
    std::fclose(file);
    errno = saved_errno;

    return success;
}

bool WriteFile(
    const std::string& path,
    const std::string& contents,
    int mode
) {
    int fd = open(
        path.c_str(),
        O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
        mode
    );

    if (fd < 0) {
        return false;
    }

    size_t written = 0;

    while (written < contents.size()) {
        ssize_t result = write(
            fd,
            contents.data() + written,
            contents.size() - written
        );

        if (result < 0) {
            if (errno == EINTR) {
                continue;
            }

            int saved_errno = errno;
            close(fd);
            errno = saved_errno;
            return false;
        }

        if (result == 0) {
            close(fd);
            errno = EIO;
            return false;
        }

        written += static_cast<size_t>(result);
    }

    return close(fd) == 0;
}

bool EnsureDirectory(const std::string& path, int mode) {
    if (path.empty()) {
        errno = EINVAL;
        return false;
    }

    if (IsDirectory(path)) {
        return true;
    }

    if (PathExists(path)) {
        errno = ENOTDIR;
        return false;
    }

    std::string current;
    size_t position = 0;

    if (path[0] == '/') {
        current = "/";
        position = 1;
    }

    while (position <= path.size()) {
        size_t next = path.find('/', position);

        std::string part = path.substr(
            position,
            next == std::string::npos
                ? std::string::npos
                : next - position
        );

        if (!part.empty() && part != ".") {
            if (!current.empty() && current != "/") {
                current += "/";
            }

            current += part;

            if (mkdir(current.c_str(), mode) != 0) {
                if (errno != EEXIST || !IsDirectory(current)) {
                    return false;
                }
            }
        }

        if (next == std::string::npos) {
            break;
        }

        position = next + 1;
    }

    return IsDirectory(path);
}

}
}
