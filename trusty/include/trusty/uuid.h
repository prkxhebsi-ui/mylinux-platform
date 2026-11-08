#ifndef MYLINUX_TRUSTY_UUID_H
#define MYLINUX_TRUSTY_UUID_H

#include <stdint.h>

typedef struct {
    uint32_t time_low;
    uint16_t time_mid;
    uint16_t time_hi;
    uint8_t clock_seq[2];
    uint8_t node[6];
} trusty_uuid_t;

int trusty_uuid_is_valid(const trusty_uuid_t *uuid);

#endif
