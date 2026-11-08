#ifndef MYLINUX_SYSCALL_POLICY_H
#define MYLINUX_SYSCALL_POLICY_H

#include <stdint.h>

enum mylinux_syscall_policy_action {
    MYLINUX_SYSCALL_ALLOW = 0,
    MYLINUX_SYSCALL_DENY,
    MYLINUX_SYSCALL_AUDIT
};

enum mylinux_syscall_policy_id {
    MYLINUX_POLICY_MOUNT = 1,
    MYLINUX_POLICY_UMOUNT2,
    MYLINUX_POLICY_LSFD_ACCESS,
    MYLINUX_POLICY_SYSFS_ACCESS
};

struct mylinux_syscall_policy_entry {
    uint32_t policy_id;
    uint32_t action;
    const char *name;
    const char *reason;
};

enum mylinux_syscall_policy_action
mylinux_policy_decide(uint32_t policy_id);

int mylinux_policy_is_restricted(void);

#endif
