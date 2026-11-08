#ifndef MYLINUX_METADATA_H
#define MYLINUX_METADATA_H

#include <stdint.h>

#define MYLINUX_METADATA_ABI 1

enum mylinux_metadata_kind {
    MYLINUX_META_PLATFORM = 1,
    MYLINUX_META_LIBRARY,
    MYLINUX_META_FEATURE,
    MYLINUX_META_SYSCALL,
    MYLINUX_META_BOOT
};

struct mylinux_metadata {
    const char *key;
    const char *value;
    uint32_t kind;
    uint32_t version;
};

#define MYLINUX_METADATA(key_, value_, kind_, version_) \
    const struct mylinux_metadata mylinux_meta_##key_ \
    __attribute__((used, section(".rodata.mylinux.metadata"))) = { \
        #key_, value_, kind_, version_ \
    }

#endif
