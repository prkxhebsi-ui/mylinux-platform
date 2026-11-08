#ifndef MYLINUX_FEATURES_H
#define MYLINUX_FEATURES_H

#include <stdint.h>

enum mylinux_feature_id {
    MYLINUX_FEATURE_MATH_BASIC = 1,
    MYLINUX_FEATURE_MATH_ADVANCED,
    MYLINUX_FEATURE_SYSCALL_MOUNT,
    MYLINUX_FEATURE_SYSCALL_MEMORY,
    MYLINUX_FEATURE_BOOT_METADATA,
    MYLINUX_FEATURE_SYMBOL_REGISTRY
};

struct mylinux_feature {
    const char *name;
    uint32_t id;
    uint32_t abi_version;
    uint64_t capabilities;
};

#define MYLINUX_FEATURE(name_, id_, version_, caps_) \
    const struct mylinux_feature mylinux_feature_##name_ \
    __attribute__((used, section(".rodata.mylinux.features"))) = { \
        #name_, id_, version_, caps_ \
    }

#endif
