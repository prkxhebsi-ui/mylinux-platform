#include <mylinux/cstring.h>

size_t
mylinux_strlen(const char *string)
{
    const char *p = string;

    if (p == 0)
        return 0;

    while (*p)
        ++p;

    return (size_t)(p - string);
}

int
mylinux_strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) {
        ++a;
        ++b;
    }

    return (unsigned char)*a - (unsigned char)*b;
}

int
mylinux_strncmp(const char *a, const char *b, size_t count)
{
    while (count && *a && *a == *b) {
        ++a;
        ++b;
        --count;
    }

    if (!count)
        return 0;

    return (unsigned char)*a - (unsigned char)*b;
}

char *
mylinux_strcpy(char *destination, const char *source)
{
    char *result = destination;

    while ((*destination++ = *source++) != '\0')
        ;

    return result;
}

char *
mylinux_strncpy(char *destination, const char *source, size_t count)
{
    char *result = destination;

    while (count && *source) {
        *destination++ = *source++;
        --count;
    }

    while (count--) 
        *destination++ = '\0';

    return result;
}

char *
mylinux_strchr(const char *string, int character)
{
    while (*string) {
        if (*string == (char)character)
            return (char *)string;

        ++string;
    }

    return character == '\0' ? (char *)string : 0;
}

void *
mylinux_memcpy(void *destination, const void *source, size_t size)
{
    unsigned char *d = destination;
    const unsigned char *s = source;

    for (size_t i = 0; i < size; ++i)
        d[i] = s[i];

    return destination;
}

void *
mylinux_memmove(void *destination, const void *source, size_t size)
{
    unsigned char *d = destination;
    const unsigned char *s = source;

    if (d < s) {
        for (size_t i = 0; i < size; ++i)
            d[i] = s[i];
    } else if (d > s) {
        while (size) {
            --size;
            d[size] = s[size];
        }
    }

    return destination;
}

void *
mylinux_memset(void *destination, int value, size_t size)
{
    unsigned char *d = destination;

    for (size_t i = 0; i < size; ++i)
        d[i] = (unsigned char)value;

    return destination;
}

int
mylinux_memcmp(const void *a, const void *b, size_t size)
{
    const unsigned char *x = a;
    const unsigned char *y = b;

    for (size_t i = 0; i < size; ++i) {
        if (x[i] != y[i])
            return (int)x[i] - (int)y[i];
    }

    return 0;
}
