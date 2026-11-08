#include <mylinux/runtime.h>

#include <errno.h>

int
mylinux_runtime_boot_main(void)
{
    return mylinux_runtime_boot();
}

int
mylinux_runtime_root_main(void)
{
    /*
     * Root-process initialization hook.
     *
     * This is not permission to perform unrestricted operations.
     * The eventual root service must install its security policy
     * before starting untrusted processes.
     */

    if (mylinux_runtime_get_state() != MYLINUX_RUNTIME_READY) {
        errno = EPERM;
        return -1;
    }

    return 0;
}
