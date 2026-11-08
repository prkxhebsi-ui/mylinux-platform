#ifndef MYLINUX_IOSTREAM_H
#define MYLINUX_IOSTREAM_H

#include <stddef.h>
#include <sys/types.h>

struct mylinux_stream {
    int fd;
    int error;
    int eof;
    unsigned int flags;
};

int mylinux_stream_open(struct mylinux_stream *stream, int fd);
ssize_t mylinux_stream_read(
    struct mylinux_stream *stream,
    void *buffer,
    size_t size
);
ssize_t mylinux_stream_write(
    struct mylinux_stream *stream,
    const void *buffer,
    size_t size
);
int mylinux_stream_flush(struct mylinux_stream *stream);
int mylinux_stream_close(struct mylinux_stream *stream);

extern struct mylinux_stream mylinux_stdin;
extern struct mylinux_stream mylinux_stdout;
extern struct mylinux_stream mylinux_stderr;

#endif
