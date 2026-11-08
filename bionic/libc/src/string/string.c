#include <stddef.h>
#include <stdint.h>
#include <string.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < n; ++i)
        d[i] = s[i];

    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d == s || n == 0)
        return dest;

    if ((uintptr_t)d < (uintptr_t)s) {
        for (size_t i = 0; i < n; ++i)
            d[i] = s[i];
    } else {
        for (size_t i = n; i != 0; --i)
            d[i - 1] = s[i - 1];
    }

    return dest;
}

void *memset(void *dest, int value, size_t n)
{
    unsigned char *d = (unsigned char *)dest;

    for (size_t i = 0; i < n; ++i)
        d[i] = (unsigned char)value;

    return dest;
}

int memcmp(const void *lhs, const void *rhs, size_t n)
{
    const unsigned char *a = (const unsigned char *)lhs;
    const unsigned char *b = (const unsigned char *)rhs;

    for (size_t i = 0; i < n; ++i) {
        if (a[i] != b[i])
            return (int)a[i] - (int)b[i];
    }

    return 0;
}

size_t strlen(const char *str)
{
    size_t n = 0;

    while (str[n] != '\0')
        ++n;

    return n;
}

size_t strnlen(const char *str, size_t maxlen)
{
    size_t n = 0;

    while (n < maxlen && str[n] != '\0')
        ++n;

    return n;
}

char *strcpy(char *restrict dest, const char *restrict src)
{
    char *result = dest;

    while ((*dest++ = *src++) != '\0')
        ;

    return result;
}

char *strncpy(char *restrict dest, const char *restrict src, size_t n)
{
    size_t i = 0;

    for (; i < n && src[i] != '\0'; ++i)
        dest[i] = src[i];

    for (; i < n; ++i)
        dest[i] = '\0';

    return dest;
}

char *strcat(char *restrict dest, const char *restrict src)
{
    char *result = dest;

    while (*dest != '\0')
        ++dest;

    while ((*dest++ = *src++) != '\0')
        ;

    return result;
}

char *strncat(char *restrict dest, const char *restrict src, size_t n)
{
    char *result = dest;

    while (*dest != '\0')
        ++dest;

    size_t i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
    return result;
}

int strcmp(const char *lhs, const char *rhs)
{
    while (*lhs != '\0' && *lhs == *rhs) {
        ++lhs;
        ++rhs;
    }

    return (int)(unsigned char)*lhs -
           (int)(unsigned char)*rhs;
}

int strncmp(const char *lhs, const char *rhs, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        unsigned char a = (unsigned char)lhs[i];
        unsigned char b = (unsigned char)rhs[i];

        if (a != b || a == '\0')
            return (int)a - (int)b;
    }

    return 0;
}

char *strchr(const char *str, int character)
{
    char target = (char)character;

    for (;;) {
        if (*str == target)
            return (char *)str;

        if (*str == '\0')
            return NULL;

        ++str;
    }
}

char *strrchr(const char *str, int character)
{
    const char *last = NULL;
    char target = (char)character;

    for (;;) {
        if (*str == target)
            last = str;

        if (*str == '\0')
            break;

        ++str;
    }

    return (char *)last;
}

char *strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;

    for (; *haystack != '\0'; ++haystack) {
        const char *h = haystack;
        const char *n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n) {
            ++h;
            ++n;
        }

        if (*n == '\0')
            return (char *)haystack;
    }

    return NULL;
}
