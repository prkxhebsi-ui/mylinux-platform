#include <sys/mount.h>
#include "../../private/errno_internal.h"

#if !defined(__aarch64__)
#error "This mount implementation currently supports AArch64 only"
#endif

#define MYLINUX_SYS_MOUNT 40
#define MYLINUX_SYS_UMOUNT2 39

static long mylinux_syscall5(
    long number,
    long arg0,
    long arg1,
    long arg2,
    long arg3,
    long arg4
) {
    register long x0 __asm__("x0") = arg0;
    register long x1 __asm__("x1") = arg1;
    register long x2 __asm__("x2") = arg2;
    register long x3 __asm__("x3") = arg3;
    register long x4 __asm__("x4") = arg4;
    register long x8 __asm__("x8") = number;

    __asm__ volatile(
        "svc 0"
        : "+r"(x0)
        : "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x8)
        : "memory", "cc"
    );

    return x0;
}

static int mylinux_finish_syscall(long result) {
    if ((unsigned long)result >= (unsigned long)-4095) {
        *__errno() = (int)-result;
        return -1;
    }

    return (int)result;
}

int mount(
    const char *source,
    const char *target,
    const char *filesystemtype,
    unsigned long mountflags,
    const void *data
) {
    long result = mylinux_syscall5(
        MYLINUX_SYS_MOUNT,
        (long)source,
        (long)target,
        (long)filesystemtype,
        (long)mountflags,
        (long)data
    );

    return mylinux_finish_syscall(result);
}

int umount2(const char *target, int flags) {
    long result = mylinux_syscall5(
        MYLINUX_SYS_UMOUNT2,
        (long)target,
        (long)flags,
        0,
        0,
        0
    );

    return mylinux_finish_syscall(result);
}

int umount(const char *target) {
    return umount2(target, 0);
}
