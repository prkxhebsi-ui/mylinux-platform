#include "ogg/ogg.h"

#include <string.h>

static uint32_t read32(const unsigned char *p) {
    return (uint32_t)p[0] |
           ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static uint64_t read64(const unsigned char *p) {
    return (uint64_t)read32(p) |
           ((uint64_t)read32(p + 4) << 32);
}

uint32_t ogg_crc32(const unsigned char *data, size_t length) {
    uint32_t crc = 0;

    for (size_t i = 0; i < length; i++) {
        crc ^= (uint32_t)data[i] << 24;

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x80000000U)
                crc = (crc << 1) ^ 0x04c11db7U;
            else
                crc <<= 1;
        }
    }

    return crc;
}

const char *ogg_version(void) {
    return "MyLinux libogg 1.0";
}

int ogg_page_parse(
    const unsigned char *data,
    size_t length,
    ogg_page *page
) {
    if (!data || !page || length < OGG_HEADER_SIZE)
        return -1;

    if (memcmp(data, "OggS", 4) != 0)
        return -2;

    if (data[4] != 0)
        return -3;

    uint8_t count = data[26];

    if (length < OGG_HEADER_SIZE + count)
        return -4;

    size_t body_size = 0;

    for (unsigned int i = 0; i < count; i++) {
        body_size += data[OGG_HEADER_SIZE + i];
    }

    size_t header_size = OGG_HEADER_SIZE + count;

    if (body_size > length - header_size)
        return -5;

    page->version = data[4];
    page->header_type = data[5];
    page->granule_position = (int64_t)read64(data + 6);
    page->serial_number = read32(data + 14);
    page->page_number = read32(data + 18);
    page->checksum = read32(data + 22);
    page->segment_count = count;

    memcpy(page->segments, data + OGG_HEADER_SIZE, count);

    page->header_size = header_size;
    page->body_size = body_size;

    return 0;
}
