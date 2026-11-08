#include <mylinux/syscall.h>

#include <errno.h>

static mylinux_syscall_backend active_backend;

int
mylinux_syscall_set_backend(mylinux_syscall_backend backend)
{
    if (backend == 0) {
        errno = EINVAL;
        return -1;
    }

    active_backend = backend;
    return 0;
}

long
mylinux_syscall_invoke(
    uint32_t id,
    uintptr_t a0,
    uintptr_t a1,
    uintptr_t a2,
    uintptr_t a3,
    uintptr_t a4,
    uintptr_t a5)
{
    const uintptr_t args[6] = {
        a0, a1, a2, a3, a4, a5
    };

    if (active_backend == 0) {
        errno = ENOSYS;
        return -1;
    }

    return active_backend(id, args);
}
