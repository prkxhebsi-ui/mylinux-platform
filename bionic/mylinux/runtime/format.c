#include <mylinux/format.h>

#include <stdio.h>
#include <errno.h>

int
mylinux_vformat(
    char *destination,
    size_t capacity,
    const char *format,
    va_list arguments)
{
    if (destination == 0 || format == 0 || capacity == 0) {
        errno = EINVAL;
        return -1;
    }

    int result = vsnprintf(
        destination,
        capacity,
        format,
        arguments
    );

    if (result < 0)
        return -1;

    return result;
}

int
mylinux_format(
    char *destination,
    size_t capacity,
    const char *format,
    ...)
{
    va_list arguments;
    va_start(arguments, format);

    int result = mylinux_vformat(
        destination,
        capacity,
        format,
        arguments
    );

    va_end(arguments);
    return result;
}
