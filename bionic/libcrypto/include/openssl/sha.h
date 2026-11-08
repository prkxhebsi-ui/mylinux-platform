#ifndef MYLIBCRYPTO_OPENSSL_SHA_H
#define MYLIBCRYPTO_OPENSSL_SHA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHA256_DIGEST_LENGTH 32
#define SHA512_DIGEST_LENGTH 64

unsigned char *SHA256(
    const unsigned char *data,
    size_t length,
    unsigned char *output
);

unsigned char *SHA512(
    const unsigned char *data,
    size_t length,
    unsigned char *output
);

#ifdef __cplusplus
}
#endif

#endif
