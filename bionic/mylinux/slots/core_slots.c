#include <mylinux/slots.h>

MYLINUX_SLOT(math_core, 1, 0);
MYLINUX_SLOT(basic_math, 2, 0);
MYLINUX_SLOT(advanced_math, 3, 0);
MYLINUX_SLOT(syscall_core, 4, 0);
MYLINUX_SLOT(mount_slot, 5, 0);
MYLINUX_SLOT(restricted_mount_slot, 6, 0);
MYLINUX_SLOT(memory_syscalls, 7, 0);

MYLINUX_SLOT_RELATION(
    basic_math_alias,
    2, 1,
    MYLINUX_SLOT_ALIAS
);

MYLINUX_SLOT_RELATION(
    advanced_math_dependency,
    3, 2,
    MYLINUX_SLOT_DEPENDS
);

MYLINUX_SLOT_RELATION(
    mount_exclusion,
    5, 6,
    MYLINUX_SLOT_EXCLUDES
);

MYLINUX_SLOT_RELATION(
    memory_dependency,
    7, 4,
    MYLINUX_SLOT_DEPENDS
);
