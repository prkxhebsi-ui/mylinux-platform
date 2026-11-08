#ifndef MYLINUX_BOOT_METADATA_H
#define MYLINUX_BOOT_METADATA_H

#include <stdint.h>

#define MYLINUX_BOOT_METADATA_VERSION 1

struct mylinux_boot_metadata {
    uint64_t magic;
    uint32_t version;
    uint32_t structure_size;

    const char *platform_name;
    const char *platform_version;
    const char *abi_name;

    uint64_t feature_mask;
    uint64_t flags;
};

#define MYLINUX_BOOT_MAGIC UINT64_C(0x4D594C42544D4554)

#define MYLINUX_BOOT_METADATA(name_, version_, abi_, features_, flags_) \
    const struct mylinux_boot_metadata mylinux_boot_##name_ \
    __attribute__((used, section(".rodata.mylinux.boot"))) = { \
        MYLINUX_BOOT_MAGIC, \
        MYLINUX_BOOT_METADATA_VERSION, \
        sizeof(struct mylinux_boot_metadata), \
        "MyLinux", version_, abi_, features_, flags_ \
    }

#endif
