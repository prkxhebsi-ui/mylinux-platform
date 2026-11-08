#ifndef MYLINUX_X86_64_TYPES_H
#define MYLINUX_X86_64_TYPES_H

#include <stdint.h>

#define MYLINUX_ARCH_BITS 64
#define MYLINUX_ARCH_NAME "x86_64"
#define MYLINUX_PAGE_SIZE 4096

typedef uint64_t mylinux_register_t;
typedef int64_t mylinux_sregister_t;

#endif
