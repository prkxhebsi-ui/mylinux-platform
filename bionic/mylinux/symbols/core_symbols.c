#include <mylinux/symbol.h>

MYLINUX_SYMBOL(math_add, "MYLINUX_1.0", 0x1001,
               MYLINUX_SYMBOL_FUNCTION, 0);

MYLINUX_SYMBOL(math_mul, "MYLINUX_1.0", 0x1002,
               MYLINUX_SYMBOL_FUNCTION, 0);

MYLINUX_SYMBOL(syscall_mount, "MYLINUX_1.0", 0x2001,
               MYLINUX_SYMBOL_SYSCALL, 0);

MYLINUX_SYMBOL(syscall_mmap, "MYLINUX_1.0", 0x2002,
               MYLINUX_SYMBOL_SYSCALL, 0);
