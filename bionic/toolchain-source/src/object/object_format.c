#include "object_format.h"

#include <stddef.h>

ToolchainObjectFormat toolchain_detect_object_format(
    const unsigned char *data, unsigned long size)
{
    static const unsigned char elf_magic[] = {
        0x7f, 'E', 'L', 'F'
    };

    static const unsigned char archive_magic[] = {
        '!', '<', 'a', 'r', 'c', 'h', '>', '\n'
    };

    if (data == NULL) {
        return TOOLCHAIN_OBJECT_UNKNOWN;
    }

    if (size >= sizeof(elf_magic)) {
        size_t i;
        for (i = 0; i < sizeof(elf_magic); ++i) {
            if (data[i] != elf_magic[i]) {
                break;
            }
        }
        if (i == sizeof(elf_magic)) {
            return TOOLCHAIN_OBJECT_ELF;
        }
    }

    if (size >= sizeof(archive_magic)) {
        size_t i;
        for (i = 0; i < sizeof(archive_magic); ++i) {
            if (data[i] != archive_magic[i]) {
                break;
            }
        }
        if (i == sizeof(archive_magic)) {
            return TOOLCHAIN_OBJECT_ARCHIVE;
        }
    }

    return TOOLCHAIN_OBJECT_UNKNOWN;
}
