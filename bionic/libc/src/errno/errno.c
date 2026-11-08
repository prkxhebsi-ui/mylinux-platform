#include "../../private/errno_internal.h"

/*
 * Each thread gets its own errno value.
 * A complete libc will integrate this with its TLS runtime.
 */
static __thread int mylinux_errno_value;

int *__errno(void) {
    return &mylinux_errno_value;
}
