#ifndef MYLINUX_MACHINE_TYPES_H
#define MYLINUX_MACHINE_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef intptr_t mylinux_intptr_t;
typedef uintptr_t mylinux_uintptr_t;

#if UINTPTR_MAX == UINT64_MAX
#define MYLINUX_POINTER_BITS 64
#elif UINTPTR_MAX == UINT32_MAX
#define MYLINUX_POINTER_BITS 32
#else
#error Unsupported pointer width
#endif

#endif
