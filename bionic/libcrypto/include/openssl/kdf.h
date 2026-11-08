#ifndef MYLIBCRYPTO_OPENSSL_KDF_H
#define MYLIBCRYPTO_OPENSSL_KDF_H

#include <stddef.h>
#include <openssl/evp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct evp_kdf_st EVP_KDF;
typedef struct evp_kdf_ctx_st EVP_KDF_CTX;

const EVP_KDF *EVP_KDF_fetch(
    void *library_context,
    const char *algorithm,
    const char *properties
);

EVP_KDF_CTX *EVP_KDF_CTX_new(const EVP_KDF *kdf);
void EVP_KDF_CTX_free(EVP_KDF_CTX *context);

int EVP_KDF_derive(
    EVP_KDF_CTX *context,
    unsigned char *output,
    size_t output_length,
    const void *parameters
);

#ifdef __cplusplus
}
#endif

#endif
