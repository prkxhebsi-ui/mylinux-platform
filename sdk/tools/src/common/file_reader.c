#define _POSIX_C_SOURCE 200809L
#include "file_reader.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int sdk_read_file(const char *path, char **buffer, size_t *length)
{
    if (!path || !buffer || !length) {
        errno = EINVAL;
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0)
        return -1;

    size_t capacity = 4096;
    size_t used = 0;
    char *data = malloc(capacity + 1);

    if (!data) {
        close(fd);
        return -1;
    }

    for (;;) {
        if (used == capacity) {
            if (capacity > SIZE_MAX / 2 - 1) {
                errno = EOVERFLOW;
                free(data);
                close(fd);
                return -1;
            }

            size_t next = capacity * 2;
            char *grown = realloc(data, next + 1);

            if (!grown) {
                free(data);
                close(fd);
                return -1;
            }

            data = grown;
            capacity = next;
        }

        ssize_t n = read(fd, data + used, capacity - used);

        if (n < 0) {
            if (errno == EINTR)
                continue;

            free(data);
            close(fd);
            return -1;
        }

        if (n == 0)
            break;

        used += (size_t)n;
    }

    if (close(fd) < 0) {
        free(data);
        return -1;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 0;
}

int sdk_write_file(const char *path, const void *data, size_t length)
{
    if (!path || (!data && length != 0)) {
        errno = EINVAL;
        return -1;
    }

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
    if (fd < 0)
        return -1;

    const unsigned char *p = data;
    size_t written = 0;

    while (written < length) {
        ssize_t n = write(fd, p + written, length - written);

        if (n < 0) {
            if (errno == EINTR)
                continue;

            close(fd);
            return -1;
        }

        if (n == 0) {
            errno = EIO;
            close(fd);
            return -1;
        }

        written += (size_t)n;
    }

    return close(fd);
}
