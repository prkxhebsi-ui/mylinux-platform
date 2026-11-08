#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

#define MYFILE_MAGIC 0x4D594649u
#define MYFILE_READ  1u
#define MYFILE_WRITE 2u
#define MYFILE_EOF   4u
#define MYFILE_ERR   8u

struct mylinux_FILE {
    unsigned int magic;
    int fd;
    unsigned int flags;
    int owned;
};

static struct mylinux_FILE stream_in = {
    MYFILE_MAGIC, STDIN_FILENO, MYFILE_READ, 0
};
static struct mylinux_FILE stream_out = {
    MYFILE_MAGIC, STDOUT_FILENO, MYFILE_WRITE, 0
};
static struct mylinux_FILE stream_err = {
    MYFILE_MAGIC, STDERR_FILENO, MYFILE_WRITE, 0
};

FILE *stdin = &stream_in;
FILE *stdout = &stream_out;
FILE *stderr = &stream_err;

static int valid_stream(FILE *stream)
{
    return stream != NULL && stream->magic == MYFILE_MAGIC &&
           stream->fd >= 0;
}

static int mode_flags(const char *mode, int *flags)
{
    if (mode == NULL || mode[0] == '\0')
        return -1;

    switch (mode[0]) {
    case 'r':
        *flags = O_RDONLY;
        break;
    case 'w':
        *flags = O_WRONLY | O_CREAT | O_TRUNC;
        break;
    case 'a':
        *flags = O_WRONLY | O_CREAT | O_APPEND;
        break;
    default:
        return -1;
    }

    for (const char *p = mode + 1; *p != '\0'; ++p) {
        if (*p == '+') {
            *flags &= ~(O_RDONLY | O_WRONLY);
            *flags |= O_RDWR;
        } else if (*p != 'b' && *p != 'e' && *p != 'x') {
            return -1;
        } else if (*p == 'x') {
            *flags |= O_EXCL;
        }
    }

    return 0;
}

FILE *fopen(const char *path, const char *mode)
{
    int flags;

    if (path == NULL || mode_flags(mode, &flags) != 0) {
        errno = EINVAL;
        return NULL;
    }

    int fd = open(path, flags | O_CLOEXEC, 0666);
    if (fd < 0)
        return NULL;

    FILE *stream = malloc(sizeof(*stream));
    if (stream == NULL) {
        int saved = errno;
        close(fd);
        errno = saved;
        return NULL;
    }

    stream->magic = MYFILE_MAGIC;
    stream->fd = fd;
    stream->flags = 0;
    stream->owned = 1;

    if ((flags & O_RDONLY) != O_WRONLY)
        stream->flags |= MYFILE_READ;
    if ((flags & O_WRONLY) != O_RDONLY)
        stream->flags |= MYFILE_WRITE;

    return stream;
}

int fclose(FILE *stream)
{
    if (!valid_stream(stream)) {
        errno = EBADF;
        return EOF;
    }

    int result = 0;

    if (stream->owned)
        result = close(stream->fd);

    if (stream->owned) {
        stream->magic = 0;
        free(stream);
    }

    return result == 0 ? 0 : EOF;
}

int fflush(FILE *stream)
{
    if (stream != NULL && !valid_stream(stream)) {
        errno = EBADF;
        return EOF;
    }

    /* This initial implementation writes directly to the file descriptor. */
    return 0;
}

int fgetc(FILE *stream)
{
    if (!valid_stream(stream) || !(stream->flags & MYFILE_READ)) {
        errno = EBADF;
        return EOF;
    }

    unsigned char c;
    ssize_t n;

    do {
        n = read(stream->fd, &c, 1);
    } while (n < 0 && errno == EINTR);

    if (n == 1)
        return (int)c;

    if (n == 0) {
        stream->flags |= MYFILE_EOF;
        return EOF;
    }

    stream->flags |= MYFILE_ERR;
    return EOF;
}

int getc(FILE *stream)
{
    return fgetc(stream);
}

int getchar(void)
{
    return fgetc(stdin);
}

int fputc(int character, FILE *stream)
{
    if (!valid_stream(stream) || !(stream->flags & MYFILE_WRITE)) {
        errno = EBADF;
        return EOF;
    }

    unsigned char c = (unsigned char)character;
    ssize_t n;

    do {
        n = write(stream->fd, &c, 1);
    } while (n < 0 && errno == EINTR);

    if (n == 1)
        return (int)c;

    stream->flags |= MYFILE_ERR;
    return EOF;
}

int putc(int character, FILE *stream)
{
    return fputc(character, stream);
}

int putchar(int character)
{
    return fputc(character, stdout);
}

char *fgets(char *buffer, int size, FILE *stream)
{
    if (buffer == NULL || size <= 0) {
        errno = EINVAL;
        return NULL;
    }

    int i = 0;

    while (i < size - 1) {
        int c = fgetc(stream);

        if (c == EOF)
            break;

        buffer[i++] = (char)c;

        if (c == '\n')
            break;
    }

    if (i == 0)
        return NULL;

    buffer[i] = '\0';
    return buffer;
}

int fputs(const char *str, FILE *stream)
{
    if (str == NULL || !valid_stream(stream) ||
        !(stream->flags & MYFILE_WRITE)) {
        errno = EINVAL;
        return EOF;
    }

    size_t length = strlen(str);
    size_t done = 0;

    while (done < length) {
        ssize_t n = write(stream->fd, str + done, length - done);

        if (n < 0 && errno == EINTR)
            continue;

        if (n <= 0) {
            stream->flags |= MYFILE_ERR;
            return EOF;
        }

        done += (size_t)n;
    }

    return 0;
}

int puts(const char *str)
{
    if (fputs(str, stdout) == EOF || fputc('\n', stdout) == EOF)
        return EOF;

    return 0;
}

size_t fread(void *buffer, size_t size, size_t count, FILE *stream)
{
    if (size == 0 || count == 0)
        return 0;

    if (buffer == NULL || count > SIZE_MAX / size ||
        !valid_stream(stream) || !(stream->flags & MYFILE_READ)) {
        errno = EINVAL;
        return 0;
    }

    size_t total = size * count;
    size_t done = 0;

    while (done < total) {
        ssize_t n = read(stream->fd, (char *)buffer + done, total - done);

        if (n < 0 && errno == EINTR)
            continue;

        if (n <= 0) {
            if (n == 0)
                stream->flags |= MYFILE_EOF;
            else
                stream->flags |= MYFILE_ERR;
            break;
        }

        done += (size_t)n;
    }

    return done / size;
}

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream)
{
    if (size == 0 || count == 0)
        return 0;

    if (buffer == NULL || count > SIZE_MAX / size ||
        !valid_stream(stream) || !(stream->flags & MYFILE_WRITE)) {
        errno = EINVAL;
        return 0;
    }

    size_t total = size * count;
    size_t done = 0;

    while (done < total) {
        ssize_t n = write(stream->fd, (const char *)buffer + done,
                          total - done);

        if (n < 0 && errno == EINTR)
            continue;

        if (n <= 0) {
            stream->flags |= MYFILE_ERR;
            break;
        }

        done += (size_t)n;
    }

    return done / size;
}

int fseek(FILE *stream, long offset, int origin)
{
    if (!valid_stream(stream)) {
        errno = EBADF;
        return -1;
    }

    off_t result = lseek(stream->fd, (off_t)offset, origin);

    if (result == (off_t)-1)
        return -1;

    stream->flags &= ~MYFILE_EOF;
    return 0;
}

long ftell(FILE *stream)
{
    if (!valid_stream(stream)) {
        errno = EBADF;
        return -1L;
    }

    off_t result = lseek(stream->fd, 0, SEEK_CUR);

    if (result == (off_t)-1 || result > LONG_MAX) {
        errno = EOVERFLOW;
        return -1L;
    }

    return (long)result;
}

void rewind(FILE *stream)
{
    if (fseek(stream, 0, SEEK_SET) == 0)
        clearerr(stream);
}

int feof(FILE *stream)
{
    return valid_stream(stream) &&
           (stream->flags & MYFILE_EOF) != 0;
}

int ferror(FILE *stream)
{
    return valid_stream(stream) &&
           (stream->flags & MYFILE_ERR) != 0;
}

void clearerr(FILE *stream)
{
    if (valid_stream(stream))
        stream->flags &= ~(MYFILE_EOF | MYFILE_ERR);
}

int remove(const char *path)
{
    return unlink(path);
}

int rename(const char *old_path, const char *new_path)
{
    return (int)renameat(AT_FDCWD, old_path, AT_FDCWD, new_path);
}
