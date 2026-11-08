#include "compiler_fd.h"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int compiler_open_readonly(const char *path)
{
    if (path == 0) {
        errno = EINVAL;
        return -1;
    }

    return open(path, O_RDONLY | O_CLOEXEC);
}

int compiler_set_cloexec(int fd)
{
    int flags;

    if (fd < 0) {
        errno = EBADF;
        return -1;
    }

    flags = fcntl(fd, F_GETFD);
    if (flags < 0) {
        return -1;
    }

    return fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
}

int compiler_close_fd(int fd)
{
    if (fd < 0) {
        errno = EBADF;
        return -1;
    }

    return close(fd);
}
