#include "elf_inspect.h"

#include <elf.h>
#include <errno.h>
#include <stddef.h>

int compiler_elf_identify(const void *data, size_t size)
{
    const unsigned char *bytes = data;

    if (bytes == NULL || size < EI_NIDENT) {
        errno = EINVAL;
        return -1;
    }

    if (bytes[EI_MAG0] != ELFMAG0 ||
        bytes[EI_MAG1] != ELFMAG1 ||
        bytes[EI_MAG2] != ELFMAG2 ||
        bytes[EI_MAG3] != ELFMAG3) {
        errno = ENOEXEC;
        return -1;
    }

    if (bytes[EI_CLASS] != ELFCLASS32 &&
        bytes[EI_CLASS] != ELFCLASS64) {
        errno = ENOEXEC;
        return -1;
    }

    if (bytes[EI_DATA] != ELFDATA2LSB &&
        bytes[EI_DATA] != ELFDATA2MSB) {
        errno = ENOEXEC;
        return -1;
    }

    return bytes[EI_CLASS];
}
