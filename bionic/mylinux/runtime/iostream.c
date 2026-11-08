#include <mylinux/iostream.h>

#include <unistd.h>
#include <errno.h>

struct mylinux_stream mylinux_stdin  = { .fd = 0 };
struct mylinux_stream mylinux_stdout = { .fd = 1 };
struct mylinux_stream mylinux_stderr = { .fd = 2 };

int
mylinux_stream_open(struct mylinux_stream *stream, int fd)
{
    if (stream == 0 || fd < 0) {
        errno = EINVAL;
        return -1;
    }

    stream->fd = fd;
    stream->error = 0;
    stream->eof = 0;
    stream->flags = 0;

    return 0;
}

ssize_t
mylinux_stream_read(
    struct mylinux_stream *stream,
    void *buffer,
    size_t size)
{
    if (stream == 0 || buffer == 0) {
        errno = EINVAL;
        return -1;
    }

    ssize_t result = read(stream->fd, buffer, size);

    if (result < 0)
        stream->error = errno;
    else if (result == 0)
        stream->eof = 1;

    return result;
}

ssize_t
mylinux_stream_write(
    struct mylinux_stream *stream,
    const void *buffer,
    size_t size)
{
    if (stream == 0 || buffer == 0) {
        errno = EINVAL;
        return -1;
    }

    ssize_t result = write(stream->fd, buffer, size);

    if (result < 0)
        stream->error = errno;

    return result;
}

int
mylinux_stream_flush(struct mylinux_stream *stream)
{
    if (stream == 0) {
        errno = EINVAL;
        return -1;
    }

    /*
     * File descriptors do not necessarily have userspace buffers.
     * fsync is not appropriate for every descriptor, especially pipes
     * and terminals. This initial stream implementation has no buffer.
     */
    return 0;
}

int
mylinux_stream_close(struct mylinux_stream *stream)
{
    if (stream == 0 || stream->fd < 0) {
        errno = EINVAL;
        return -1;
    }

    int result = close(stream->fd);
    if (result == 0)
        stream->fd = -1;
    else
        stream->error = errno;

    return result;
}
