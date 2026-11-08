#include "mylinux_stdutil.h"

#include <stdint.h>
#include <string.h>

int mylib_size_add(size_t a, size_t b, size_t *result)
{
    if (result == NULL)
        return -1;

    if (a > SIZE_MAX - b)
        return -1;

    *result = a + b;
    return 0;
}

int mylib_size_mul(size_t a, size_t b, size_t *result)
{
    if (result == NULL)
        return -1;

    if (b != 0 && a > SIZE_MAX / b)
        return -1;

    *result = a * b;
    return 0;
}

size_t mylib_strnlen(const char *text, size_t maximum)
{
    size_t length = 0;

    if (text == NULL)
        return 0;

    while (length < maximum && text[length] != '\0')
        ++length;

    return length;
}

int mylib_streq(const char *a, const char *b)
{
    if (a == NULL || b == NULL)
        return a == b;

    return strcmp(a, b) == 0;
}

int mylib_starts_with(const char *text, const char *prefix)
{
    size_t length;

    if (text == NULL || prefix == NULL)
        return 0;

    length = strlen(prefix);
    return strncmp(text, prefix, length) == 0;
}

int mylib_ends_with(const char *text, const char *suffix)
{
    size_t text_length;
    size_t suffix_length;

    if (text == NULL || suffix == NULL)
        return 0;

    text_length = strlen(text);
    suffix_length = strlen(suffix);

    if (suffix_length > text_length)
        return 0;

    return memcmp(text + text_length - suffix_length,
                  suffix, suffix_length) == 0;
}

void mylib_memzero(void *memory, size_t size)
{
    volatile unsigned char *cursor =
        (volatile unsigned char *)memory;

    if (memory == NULL)
        return;

    while (size-- > 0)
        *cursor++ = 0;
}
