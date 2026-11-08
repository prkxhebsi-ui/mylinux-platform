#ifndef MYLIBCRYPTO_CRYPTO_TYPES_H
#define MYLIBCRYPTO_CRYPTO_TYPES_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t crypto_u8;
typedef uint16_t crypto_u16;
typedef uint32_t crypto_u32;
typedef uint64_t crypto_u64;

typedef struct {
    const unsigned char *data;
    size_t length;
} crypto_const_buffer;

typedef struct {
    unsigned char *data;
    size_t length;
} crypto_buffer;

#endif
