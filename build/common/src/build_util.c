#include "mylinux/build_util.h"

#include <ctype.h>
#include <errno.h>
#include <unistd.h>

int mylinux_build_name_valid(const char *name)
{
    const unsigned char *p = (const unsigned char *)name;

    if (p == NULL || *p == '\0')
        return 0;

    if (!(isalpha(*p) || *p == '_'))
        return 0;

    for (++p; *p != '\0'; ++p) {
        if (!(isalnum(*p) || *p == '_' || *p == '-' || *p == '.'))
            return 0;
    }

    return 1;
}

int mylinux_build_relative_path_valid(const char *path)
{
    const char *p;
    const char *component;

    if (path == NULL || path[0] == '\0' || path[0] == '/')
        return 0;

    component = path;

    for (p = path; ; ++p) {
        if (*p == '\\')
            return 0;

        if (*p == '/' || *p == '\0') {
            size_t length = (size_t)(p - component);

            if (length == 0)
                return 0;

            if (length == 1 && component[0] == '.')
                return 0;

            if (length == 2 &&
                component[0] == '.' && component[1] == '.')
                return 0;

            if (*p == '\0')
                break;

            component = p + 1;
        }
    }

    return 1;
}

int mylinux_build_write_all(int fd, const void *data, size_t size)
{
    const unsigned char *p = (const unsigned char *)data;

    if (fd < 0 || (data == NULL && size != 0)) {
        errno = EINVAL;
        return -1;
    }

    while (size != 0) {
        ssize_t written = write(fd, p, size);

        if (written < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }

        if (written == 0) {
            errno = EIO;
            return -1;
        }

        p += (size_t)written;
        size -= (size_t)written;
    }

    return 0;
}
