#ifndef MYLIBCRYPTO_OPENSSL_EVP_MAC_H
#define MYLIBCRYPTO_OPENSSL_EVP_MAC_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct evp_mac_st EVP_MAC;
typedef struct evp_mac_ctx_st EVP_MAC_CTX;

const EVP_MAC *EVP_MAC_fetch(
    void *library_context,
    const char *algorithm,
    const char *properties
);

EVP_MAC_CTX *EVP_MAC_CTX_new(const EVP_MAC *mac);
void EVP_MAC_CTX_free(EVP_MAC_CTX *context);

int EVP_MAC_init(
    EVP_MAC_CTX *context,
    const unsigned char *key,
    size_t key_length,
    const void *parameters
);

int EVP_MAC_update(
    EVP_MAC_CTX *context,
    const unsigned char *data,
    size_t data_length
);

int EVP_MAC_final(
    EVP_MAC_CTX *context,
    unsigned char *output,
    size_t *output_length,
    size_t output_size
);

size_t EVP_MAC_CTX_get_mac_size(const EVP_MAC_CTX *context);

#ifdef __cplusplus
}
#endif

#endif
