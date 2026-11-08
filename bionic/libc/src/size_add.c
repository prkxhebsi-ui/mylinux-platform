#include "mylinux_libc.h"

#include <stdint.h>

int mylinux_size_add(size_t left, size_t right, size_t *result) {
    if (!result || right > SIZE_MAX - left)
        return -1;

    *result = left + right;
    return 0;
}
