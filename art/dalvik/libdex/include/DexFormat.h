#ifndef MYLINUX_DEX_FORMAT_H
#define MYLINUX_DEX_FORMAT_H

#include <stdint.h>
#include <stddef.h>

#define DEX_HEADER_SIZE 112
#define DEX_ENDIAN_CONSTANT 0x12345678U
#define DEX_REVERSE_ENDIAN_CONSTANT 0x78563412U

#define DEX_STRING_ID_SIZE 4
#define DEX_TYPE_ID_SIZE 4
#define DEX_PROTO_ID_SIZE 12
#define DEX_FIELD_ID_SIZE 8
#define DEX_METHOD_ID_SIZE 8
#define DEX_CLASS_DEF_SIZE 32

typedef struct {
    uint8_t magic[8];
    uint32_t checksum;
    uint8_t signature[20];

    uint32_t file_size;
    uint32_t header_size;
    uint32_t endian_tag;

    uint32_t link_size;
    uint32_t link_off;
    uint32_t map_off;

    uint32_t string_ids_size;
    uint32_t string_ids_off;

    uint32_t type_ids_size;
    uint32_t type_ids_off;

    uint32_t proto_ids_size;
    uint32_t proto_ids_off;

    uint32_t field_ids_size;
    uint32_t field_ids_off;

    uint32_t method_ids_size;
    uint32_t method_ids_off;

    uint32_t class_defs_size;
    uint32_t class_defs_off;

    uint32_t data_size;
    uint32_t data_off;
} DexHeader;

typedef struct {
    uint32_t utf16_size;
    const char *data;
    size_t byte_length;
} DexStringData;

#endif
