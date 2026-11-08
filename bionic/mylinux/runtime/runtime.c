#include <mylinux/runtime.h>
#include <mylinux/runtime_metadata.h>

#include <errno.h>

static struct mylinux_runtime_info runtime_info = {
    .abi_version = MYLINUX_RUNTIME_ABI,
    .state = MYLINUX_RUNTIME_COLD,
    .features =
        MYLINUX_RT_FEATURE_CSTRING |
        MYLINUX_RT_FEATURE_IOSTREAM |
        MYLINUX_RT_FEATURE_FORMAT |
        MYLINUX_RT_FEATURE_MEMORY |
        MYLINUX_RT_FEATURE_SYMBOLS |
        MYLINUX_RT_FEATURE_SYSCALLS |
        MYLINUX_RT_FEATURE_SECURITY,
    .name = MYLINUX_RUNTIME_NAME,
    .version = "0.1.0",
    .architecture = "aarch64"
};

MYLINUX_ART_METADATA(
    runtime,
    "LMyLinux/Runtime;",
    0x10000001,
    MYLINUX_ART_RUNTIME,
    1,
    0
);

int
mylinux_runtime_initialize(void)
{
    if (runtime_info.state != MYLINUX_RUNTIME_COLD) {
        errno = EALREADY;
        return -1;
    }

    runtime_info.state = MYLINUX_RUNTIME_BOOTING;

    /*
     * Registry initialization, syscall policy setup and
     * runtime subsystem initialization will be connected here.
     */

    runtime_info.state = MYLINUX_RUNTIME_READY;
    return 0;
}

int
mylinux_runtime_boot(void)
{
    return mylinux_runtime_initialize();
}

int
mylinux_runtime_shutdown(void)
{
    if (runtime_info.state != MYLINUX_RUNTIME_READY &&
        runtime_info.state != MYLINUX_RUNTIME_RESTRICTED) {
        errno = EINVAL;
        return -1;
    }

    runtime_info.state = MYLINUX_RUNTIME_COLD;
    return 0;
}

enum mylinux_runtime_state
mylinux_runtime_get_state(void)
{
    return (enum mylinux_runtime_state)runtime_info.state;
}

const struct mylinux_runtime_info *
mylinux_runtime_get_info(void)
{
    return &runtime_info;
}

int
mylinux_runtime_has_feature(uint64_t feature)
{
    return (runtime_info.features & feature) == feature;
}
