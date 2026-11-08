#ifndef MYLINUX_OGG_H
#define MYLINUX_OGG_H

#include <stddef.h>
#include <stdint.h>

#define OGG_HEADER_SIZE 27
#define OGG_MAX_SEGMENTS 255

typedef struct {
    uint8_t version;
    uint8_t header_type;
    int64_t granule_position;
    uint32_t serial_number;
    uint32_t page_number;
    uint32_t checksum;
    uint8_t segment_count;
    uint8_t segments[OGG_MAX_SEGMENTS];
    size_t header_size;
    size_t body_size;
} ogg_page;

int ogg_page_parse(
    const unsigned char *data,
    size_t length,
    ogg_page *page
);

uint32_t ogg_crc32(const unsigned char *data, size_t length);
const char *ogg_version(void);

#endif
