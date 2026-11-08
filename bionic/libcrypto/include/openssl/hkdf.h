#ifndef MYLIBCRYPTO_OPENSSL_HKDF_H
#define MYLIBCRYPTO_OPENSSL_HKDF_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int HKDF(
    unsigned char *output,
    size_t output_length,
    const EVP_MD *digest,
    const unsigned char *secret,
    size_t secret_length,
    const unsigned char *salt,
    size_t salt_length,
    const unsigned char *info,
    size_t info_length
);

#ifdef __cplusplus
}
#endif

#endif
