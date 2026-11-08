#ifndef MYLINUX_SYSCALL_NUMBERS_H
#define MYLINUX_SYSCALL_NUMBERS_H

/*
 * Linux AArch64 syscall ABI numbers.
 * Do not use these numbers on other architectures.
 */

#define MYLINUX_NR_umount2   39
#define MYLINUX_NR_mount     40
#define MYLINUX_NR_brk      214
#define MYLINUX_NR_munmap   215
#define MYLINUX_NR_mmap     222
#define MYLINUX_NR_mprotect 226

#endif
