#ifndef MYLINUX_CSTRING_H
#define MYLINUX_CSTRING_H

#include <stddef.h>

size_t mylinux_strlen(const char *string);
int mylinux_strcmp(const char *a, const char *b);
int mylinux_strncmp(const char *a, const char *b, size_t count);
char *mylinux_strcpy(char *destination, const char *source);
char *mylinux_strncpy(char *destination, const char *source, size_t count);
char *mylinux_strchr(const char *string, int character);
void *mylinux_memcpy(void *destination, const void *source, size_t size);
void *mylinux_memmove(void *destination, const void *source, size_t size);
void *mylinux_memset(void *destination, int value, size_t size);
int mylinux_memcmp(const void *a, const void *b, size_t size);

#endif
