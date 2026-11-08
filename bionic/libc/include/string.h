#ifndef MYLINUX_STRING_H
#define MYLINUX_STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *restrict dest, const void *restrict src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int value, size_t n);
int memcmp(const void *lhs, const void *rhs, size_t n);

size_t strlen(const char *str);
size_t strnlen(const char *str, size_t maxlen);
char *strcpy(char *restrict dest, const char *restrict src);
char *strncpy(char *restrict dest, const char *restrict src, size_t n);
char *strcat(char *restrict dest, const char *restrict src);
char *strncat(char *restrict dest, const char *restrict src, size_t n);

int strcmp(const char *lhs, const char *rhs);
int strncmp(const char *lhs, const char *rhs, size_t n);
char *strchr(const char *str, int character);
char *strrchr(const char *str, int character);
char *strstr(const char *haystack, const char *needle);

#ifdef __cplusplus
}
#endif

#endif
