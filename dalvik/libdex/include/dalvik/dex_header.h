#ifndef MYLINUX_DALVIK_DEX_HEADER_H
#define MYLINUX_DALVIK_DEX_HEADER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MYLINUX_DEX_HEADER_SIZE 112U
#define MYLINUX_DEX_MAGIC_SIZE 8U

struct mylinux_dex_header {
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
};

enum mylinux_dex_status {
    MYLINUX_DEX_OK = 0,
    MYLINUX_DEX_NULL_ARGUMENT = -1,
    MYLINUX_DEX_BAD_MAGIC = -2,
    MYLINUX_DEX_BAD_HEADER_SIZE = -3,
    MYLINUX_DEX_BAD_FILE_SIZE = -4,
    MYLINUX_DEX_BAD_ENDIAN_TAG = -5,
    MYLINUX_DEX_BAD_SECTION = -6
};

/* Validate an in-memory header after the caller has checked buffer length. */
int mylinux_dex_validate_header(
    const struct mylinux_dex_header* header,
    uint32_t available_bytes);

const char* mylinux_dex_status_string(int status);

#ifdef __cplusplus
}
#endif

#endif
