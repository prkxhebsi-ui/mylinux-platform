#ifndef MYLINUX_RUNTIME_H
#define MYLINUX_RUNTIME_H

#include <stddef.h>
#include <stdint.h>

#define MYLINUX_RUNTIME_ABI 1
#define MYLINUX_RUNTIME_NAME "libmylinux"

enum mylinux_runtime_state {
    MYLINUX_RUNTIME_COLD = 0,
    MYLINUX_RUNTIME_BOOTING,
    MYLINUX_RUNTIME_READY,
    MYLINUX_RUNTIME_RESTRICTED,
    MYLINUX_RUNTIME_FAILED
};

enum mylinux_runtime_feature {
    MYLINUX_RT_FEATURE_CSTRING = 1ULL << 0,
    MYLINUX_RT_FEATURE_IOSTREAM = 1ULL << 1,
    MYLINUX_RT_FEATURE_FORMAT = 1ULL << 2,
    MYLINUX_RT_FEATURE_MEMORY = 1ULL << 3,
    MYLINUX_RT_FEATURE_SYMBOLS = 1ULL << 4,
    MYLINUX_RT_FEATURE_SYSCALLS = 1ULL << 5,
    MYLINUX_RT_FEATURE_SECURITY = 1ULL << 6
};

struct mylinux_runtime_info {
    uint32_t abi_version;
    uint32_t state;
    uint64_t features;
    const char *name;
    const char *version;
    const char *architecture;
};

int mylinux_runtime_boot(void);
int mylinux_runtime_initialize(void);
int mylinux_runtime_shutdown(void);

enum mylinux_runtime_state mylinux_runtime_get_state(void);

const struct mylinux_runtime_info *
mylinux_runtime_get_info(void);

int mylinux_runtime_has_feature(uint64_t feature);

#endif
