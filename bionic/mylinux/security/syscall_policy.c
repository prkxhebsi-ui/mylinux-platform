#include <mylinux/syscall_policy.h>

static const struct mylinux_syscall_policy_entry policies[]
__attribute__((used, section(".rodata.mylinux.security"))) = {
    {
        MYLINUX_POLICY_MOUNT,
        MYLINUX_SYSCALL_DENY,
        "mount",
        "Mount operations are restricted"
    },
    {
        MYLINUX_POLICY_UMOUNT2,
        MYLINUX_SYSCALL_DENY,
        "umount2",
        "Unmount operations are restricted"
    },
    {
        MYLINUX_POLICY_LSFD_ACCESS,
        MYLINUX_SYSCALL_DENY,
        "lsfd",
        "Access to file-descriptor inspection is restricted"
    },
    {
        MYLINUX_POLICY_SYSFS_ACCESS,
        MYLINUX_SYSCALL_DENY,
        "/sys",
        "Sysfs access is restricted"
    }
};

enum mylinux_syscall_policy_action
mylinux_policy_decide(uint32_t policy_id)
{
    for (unsigned long i = 0;
         i < sizeof(policies) / sizeof(policies[0]);
         ++i) {
        if (policies[i].policy_id == policy_id)
            return policies[i].action;
    }

    return MYLINUX_SYSCALL_ALLOW;
}

int
mylinux_policy_is_restricted(void)
{
    return 1;
}
