#ifndef MYLINUX_TARGET_INFO_H
#define MYLINUX_TARGET_INFO_H

typedef struct {
    const char *triple;
    const char *architecture;
    const char *operating_system;
    unsigned int api_level;
    unsigned int pointer_bits;
} ToolchainTarget;

const ToolchainTarget *toolchain_find_target(const char *triple);

#endif
