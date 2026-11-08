#ifndef MYLINUX_LINKER_H
#define MYLINUX_LINKER_H

#include <stddef.h>
#include <stdint.h>

struct mylinux_elf_info {
    uint8_t elf_class;
    uint8_t data_encoding;
    uint16_t machine;
    uint16_t type;
};

int mylinux_linker_inspect_elf(
    const void *image,
    size_t image_size,
    struct mylinux_elf_info *info);

#endif
