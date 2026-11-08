#define _POSIX_C_SOURCE 200809L

#include "exit_module.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>

int exit_module_parse_code(const char *text, int *code) {
    char *end = NULL;
    long value;

    if (!text || !*text || !code) return -1;

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno || !end || *end != '\0' ||
        value < 0 || value > 255) {
        return -1;
    }

    *code = (int)value;
    return 0;
}

/*
 * State file format: one unsigned decimal error count.
 * flock() serializes cooperating writers across processes.
 */
int exit_module_report_error(const char *state_file, unsigned int limit) {
    char buffer[64];
    unsigned int count = 0;
    int fd;
    ssize_t length;

    if (!state_file || !*state_file || limit == 0) return -1;

    fd = open(state_file, O_RDWR | O_CREAT | O_CLOEXEC, 0600);
    if (fd < 0) return -1;

    if (flock(fd, LOCK_EX) < 0) {
        close(fd);
        return -1;
    }

    if (lseek(fd, 0, SEEK_SET) < 0) goto fail;

    length = read(fd, buffer, sizeof(buffer) - 1);
    if (length < 0) goto fail;

    buffer[length] = '\0';

    if (length > 0) {
        char *end = NULL;
        unsigned long parsed;

        errno = 0;
        parsed = strtoul(buffer, &end, 10);
        if (errno || end == buffer || (*end && *end != '\n') ||
            parsed > UINT_MAX) {
            goto fail;
        }
        count = (unsigned int)parsed;
    }

    if (count < UINT_MAX) count++;

    if (ftruncate(fd, 0) < 0 || lseek(fd, 0, SEEK_SET) < 0)
        goto fail;

    length = snprintf(buffer, sizeof(buffer), "%u\n", count);
    if (length < 0 || (size_t)length >= sizeof(buffer))
        goto fail;

    {
        ssize_t written = write(fd, buffer, (size_t)length);
        if (written != length) goto fail;
    }

    (void)flock(fd, LOCK_UN);
    close(fd);

    return count >= limit ? 1 : 0;

fail:
    (void)flock(fd, LOCK_UN);
    close(fd);
    return -1;
}

int exit_module_read_errors(const char *state_file, unsigned int *count) {
    char buffer[64];
    char *end = NULL;
    unsigned long parsed;
    int fd;
    ssize_t length;

    if (!state_file || !count) return -1;

    fd = open(state_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0) return -1;

    length = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    if (length < 0) return -1;
    buffer[length] = '\0';

    errno = 0;
    parsed = strtoul(buffer, &end, 10);

    if (errno || end == buffer || parsed > UINT_MAX)
        return -1;

    *count = (unsigned int)parsed;
    return 0;
}
