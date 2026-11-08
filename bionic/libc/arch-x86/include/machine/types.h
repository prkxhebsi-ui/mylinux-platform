#ifndef MYLINUX_X86_TYPES_H
#define MYLINUX_X86_TYPES_H

#include <stdint.h>

#define MYLINUX_ARCH_BITS 32
#define MYLINUX_ARCH_NAME "i386"
#define MYLINUX_PAGE_SIZE 4096

typedef uint32_t mylinux_register_t;
typedef int32_t mylinux_sregister_t;

#endif
