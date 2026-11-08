#ifndef MYLINUX_OBJECT_FORMAT_H
#define MYLINUX_OBJECT_FORMAT_H

typedef enum {
    TOOLCHAIN_OBJECT_UNKNOWN = 0,
    TOOLCHAIN_OBJECT_ELF,
    TOOLCHAIN_OBJECT_ARCHIVE
} ToolchainObjectFormat;

ToolchainObjectFormat toolchain_detect_object_format(
    const unsigned char *data, unsigned long size);

#endif
