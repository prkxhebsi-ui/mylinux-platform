#ifndef MYLINUX_ARM64_SYSCALL_NUMBERS_H
#define MYLINUX_ARM64_SYSCALL_NUMBERS_H

/*
 * Linux AArch64 syscall ABI numbers.
 * These are Linux kernel ABI values, not MyLinux-assigned numbers.
 */

#define MYLINUX_ARM64_NR_umount2  39
#define MYLINUX_ARM64_NR_mount    40
#define MYLINUX_ARM64_NR_brk     214
#define MYLINUX_ARM64_NR_munmap  215
#define MYLINUX_ARM64_NR_mmap    222
#define MYLINUX_ARM64_NR_mprotect 226

#endif
