#include "mylinux_linker.h"

#include <elf.h>
#include <string.h>

int mylinux_linker_inspect_elf(
    const void *image,
    size_t image_size,
    struct mylinux_elf_info *info) {
    const unsigned char *bytes = image;

    if (!image || !info || image_size < EI_NIDENT)
        return -1;

    if (memcmp(bytes, ELFMAG, SELFMAG) != 0)
        return -1;

    if (bytes[EI_CLASS] != ELFCLASS32 &&
        bytes[EI_CLASS] != ELFCLASS64)
        return -1;

    if (bytes[EI_DATA] != ELFDATA2LSB &&
        bytes[EI_DATA] != ELFDATA2MSB)
        return -1;

    /*
     * This routine validates only the ELF identification bytes.
     * It does not load objects or relocate executable code.
     */
    info->elf_class = bytes[EI_CLASS];
    info->data_encoding = bytes[EI_DATA];
    info->machine = 0;
    info->type = 0;
    return 0;
}
