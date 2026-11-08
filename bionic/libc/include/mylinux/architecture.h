#ifndef MYLINUX_ARCHITECTURE_H
#define MYLINUX_ARCHITECTURE_H

#if defined(__aarch64__)
#define MYLINUX_ARCH_AARCH64 1
#define MYLINUX_ARCH_NAME "aarch64"

#elif defined(__x86_64__)
#define MYLINUX_ARCH_X86_64 1
#define MYLINUX_ARCH_NAME "x86_64"

#elif defined(__riscv) && __riscv_xlen == 64
#define MYLINUX_ARCH_RISCV64 1
#define MYLINUX_ARCH_NAME "riscv64"

#elif defined(__arm__)
#define MYLINUX_ARCH_ARM 1
#define MYLINUX_ARCH_NAME "arm"

#elif defined(__i386__)
#define MYLINUX_ARCH_X86 1
#define MYLINUX_ARCH_NAME "x86"

#else
#define MYLINUX_ARCH_UNKNOWN 1
#define MYLINUX_ARCH_NAME "unknown"
#endif

#endif
