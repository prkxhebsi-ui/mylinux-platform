#ifndef MYLINUX_SDK_FILE_READER_H
#define MYLINUX_SDK_FILE_READER_H

#include <stddef.h>

int sdk_read_file(const char *path, char **buffer, size_t *length);
int sdk_write_file(const char *path, const void *data, size_t length);

#endif
