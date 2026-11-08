#include <mylinux/syscall.h>

#define SYSCALL_ENTRY(name_, id_, count_) \
    const struct mylinux_syscall_descriptor mylinux_syscall_desc_##name_ \
    __attribute__((used, section(".rodata.mylinux.syscalls"))) = { \
        #name_, id_, count_, 0 \
    }

SYSCALL_ENTRY(mount,   MYLINUX_SYS_MOUNT,   5);
SYSCALL_ENTRY(umount2, MYLINUX_SYS_UMOUNT2, 2);
SYSCALL_ENTRY(mmap,    MYLINUX_SYS_MMAP,    6);
SYSCALL_ENTRY(munmap,  MYLINUX_SYS_MUNMAP,  2);
SYSCALL_ENTRY(mprotect,MYLINUX_SYS_MPROTECT,3);
SYSCALL_ENTRY(brk,     MYLINUX_SYS_BRK,     1);
