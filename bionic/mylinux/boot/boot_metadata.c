#include <mylinux/boot_metadata.h>

#include <mylinux/features.h>

MYLINUX_BOOT_METADATA(
    platform,
    "0.1.0",
    "aarch64-linux-android",
    (1ULL << MYLINUX_FEATURE_MATH_BASIC) |
    (1ULL << MYLINUX_FEATURE_SYMBOL_REGISTRY),
    0
);
