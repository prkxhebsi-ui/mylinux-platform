#include "dalvik/dex_header.h"

#include <stddef.h>
#include <string.h>

static int section_valid(uint32_t count, uint32_t offset,
                         uint32_t file_size) {
    if (count == 0U) {
        return offset == 0U;
    }

    return offset >= MYLINUX_DEX_HEADER_SIZE &&
           offset < file_size;
}

int mylinux_dex_validate_header(
    const struct mylinux_dex_header* header,
    uint32_t available_bytes) {
    static const uint8_t expected_magic[4] = {
        'd', 'e', 'x', '\n'
    };

    if (header == NULL) {
        return MYLINUX_DEX_NULL_ARGUMENT;
    }

    if (available_bytes < MYLINUX_DEX_HEADER_SIZE) {
        return MYLINUX_DEX_BAD_HEADER_SIZE;
    }

    if (memcmp(header->magic, expected_magic,
               sizeof(expected_magic)) != 0 ||
        header->magic[7] != '\0' ||
        header->magic[4] < '0' || header->magic[4] > '9' ||
        header->magic[5] < '0' || header->magic[5] > '9' ||
        header->magic[6] < '0' || header->magic[6] > '9') {
        return MYLINUX_DEX_BAD_MAGIC;
    }

    if (header->header_size != MYLINUX_DEX_HEADER_SIZE) {
        return MYLINUX_DEX_BAD_HEADER_SIZE;
    }

    if (header->file_size < MYLINUX_DEX_HEADER_SIZE ||
        header->file_size > available_bytes) {
        return MYLINUX_DEX_BAD_FILE_SIZE;
    }

    if (header->endian_tag != UINT32_C(0x12345678)) {
        return MYLINUX_DEX_BAD_ENDIAN_TAG;
    }

    if (!section_valid(header->string_ids_size,
                       header->string_ids_off, header->file_size) ||
        !section_valid(header->type_ids_size,
                       header->type_ids_off, header->file_size) ||
        !section_valid(header->method_ids_size,
                       header->method_ids_off, header->file_size) ||
        !section_valid(header->class_defs_size,
                       header->class_defs_off, header->file_size) ||
        !section_valid(header->data_size,
                       header->data_off, header->file_size)) {
        return MYLINUX_DEX_BAD_SECTION;
    }

    return MYLINUX_DEX_OK;
}

const char* mylinux_dex_status_string(int status) {
    switch (status) {
        case MYLINUX_DEX_OK:
            return "valid DEX header";
        case MYLINUX_DEX_NULL_ARGUMENT:
            return "null header";
        case MYLINUX_DEX_BAD_MAGIC:
            return "invalid DEX magic";
        case MYLINUX_DEX_BAD_HEADER_SIZE:
            return "invalid DEX header size";
        case MYLINUX_DEX_BAD_FILE_SIZE:
            return "invalid DEX file size";
        case MYLINUX_DEX_BAD_ENDIAN_TAG:
            return "unsupported endian tag";
        case MYLINUX_DEX_BAD_SECTION:
            return "invalid DEX section";
        default:
            return "unknown DEX validation status";
    }
}
