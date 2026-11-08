#ifndef MYLINUX_SYSCALL_H
#define MYLINUX_SYSCALL_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

enum mylinux_syscall_id {
    MYLINUX_SYS_MOUNT = 1,
    MYLINUX_SYS_UMOUNT2,
    MYLINUX_SYS_MMAP,
    MYLINUX_SYS_MUNMAP,
    MYLINUX_SYS_MPROTECT,
    MYLINUX_SYS_BRK
};

struct mylinux_syscall_descriptor {
    const char *name;
    uint32_t id;
    uint32_t argument_count;
    uint32_t flags;
};

typedef long (*mylinux_syscall_backend)(
    uint32_t id,
    const uintptr_t args[6]
);

int mylinux_syscall_set_backend(mylinux_syscall_backend backend);

long mylinux_syscall_invoke(
    uint32_t id,
    uintptr_t a0,
    uintptr_t a1,
    uintptr_t a2,
    uintptr_t a3,
    uintptr_t a4,
    uintptr_t a5
);

long mylinux_syscall_mount(
    const char *source,
    const char *target,
    const char *filesystem,
    unsigned long flags,
    const void *data
);

long mylinux_syscall_umount2(
    const char *target,
    int flags
);

long mylinux_syscall_mmap(
    void *address,
    size_t length,
    int protection,
    int flags,
    int fd,
    int64_t offset
);

long mylinux_syscall_munmap(
    void *address,
    size_t length
);

long mylinux_syscall_mprotect(
    void *address,
    size_t length,
    int protection
);

long mylinux_syscall_brk(void *address);

#endif
