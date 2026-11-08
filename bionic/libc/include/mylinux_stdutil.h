#ifndef MYLINUX_STDUTIL_H
#define MYLINUX_STDUTIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int mylib_size_add(size_t a, size_t b, size_t *result);
int mylib_size_mul(size_t a, size_t b, size_t *result);
size_t mylib_strnlen(const char *text, size_t maximum);
int mylib_streq(const char *a, const char *b);
int mylib_starts_with(const char *text, const char *prefix);
int mylib_ends_with(const char *text, const char *suffix);
void mylib_memzero(void *memory, size_t size);

#ifdef __cplusplus
}
#endif

#endif
