#ifndef MYLINUX_LIBC_H
#define MYLINUX_LIBC_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int mylinux_size_add(size_t left, size_t right, size_t *result);

#ifdef __cplusplus
}
#endif

#endif
