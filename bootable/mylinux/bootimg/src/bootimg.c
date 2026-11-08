#include <mylinux/bootimg.h>

#include <string.h>

enum mylinux_bootimg_status
mylinux_bootimg_check_magic(const void *data, size_t size)
{
    if (data == NULL) {
        return MYLINUX_BOOTIMG_INVALID_ARGUMENT;
    }

    if (size < MYLINUX_BOOTIMG_MAGIC_SIZE) {
        return MYLINUX_BOOTIMG_INVALID_ARGUMENT;
    }

    if (memcmp(data,
               MYLINUX_BOOTIMG_MAGIC,
               MYLINUX_BOOTIMG_MAGIC_SIZE) != 0) {
        return MYLINUX_BOOTIMG_INVALID_MAGIC;
    }

    return MYLINUX_BOOTIMG_OK;
}

const char *
mylinux_bootimg_status_string(enum mylinux_bootimg_status status)
{
    switch (status) {
    case MYLINUX_BOOTIMG_OK:
        return "success";

    case MYLINUX_BOOTIMG_INVALID_ARGUMENT:
        return "invalid argument";

    case MYLINUX_BOOTIMG_INVALID_MAGIC:
        return "invalid Android boot image magic";

    case MYLINUX_BOOTIMG_IO_ERROR:
        return "input/output error";

    default:
        return "unknown boot image error";
    }
}
