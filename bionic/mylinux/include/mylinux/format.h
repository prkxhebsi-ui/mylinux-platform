#ifndef MYLINUX_FORMAT_H
#define MYLINUX_FORMAT_H

#include <stddef.h>
#include <stdarg.h>

int mylinux_vformat(
    char *destination,
    size_t capacity,
    const char *format,
    va_list arguments
);

int mylinux_format(
    char *destination,
    size_t capacity,
    const char *format,
    ...
);

#endif
