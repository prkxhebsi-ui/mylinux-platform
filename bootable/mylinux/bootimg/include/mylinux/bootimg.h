#ifndef MYLINUX_BOOTIMG_H
#define MYLINUX_BOOTIMG_H

#include <stddef.h>
#include <stdint.h>

#define MYLINUX_BOOTIMG_MAGIC "ANDROID!"
#define MYLINUX_BOOTIMG_MAGIC_SIZE 8

enum mylinux_bootimg_status {
    MYLINUX_BOOTIMG_OK = 0,
    MYLINUX_BOOTIMG_INVALID_ARGUMENT,
    MYLINUX_BOOTIMG_INVALID_MAGIC,
    MYLINUX_BOOTIMG_IO_ERROR
};

struct mylinux_bootimg_info {
    uint32_t header_version;
    uint64_t image_size;
    int valid;
};

enum mylinux_bootimg_status
mylinux_bootimg_check_magic(const void *data, size_t size);

const char *
mylinux_bootimg_status_string(enum mylinux_bootimg_status status);

#endif
