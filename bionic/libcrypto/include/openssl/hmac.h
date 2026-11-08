#ifndef MYLIBCRYPTO_OPENSSL_HMAC_H
#define MYLIBCRYPTO_OPENSSL_HMAC_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned char *HMAC(
    const void *digest,
    const void *key,
    int key_length,
    const unsigned char *data,
    size_t data_length,
    unsigned char *output,
    unsigned int *output_length
);

#ifdef __cplusplus
}
#endif

#endif
