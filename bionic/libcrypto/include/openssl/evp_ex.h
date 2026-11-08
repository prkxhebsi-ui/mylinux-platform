#ifndef MYLIBCRYPTO_OPENSSL_EVP_EX_H
#define MYLIBCRYPTO_OPENSSL_EVP_EX_H

#include <stddef.h>
#include <openssl/evp.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EVP_MAX_MD_SIZE 64

int EVP_MD_get_size(const EVP_MD *digest);
int EVP_MD_size(const EVP_MD *digest);

int EVP_MD_CTX_reset(EVP_MD_CTX *context);
const EVP_MD *EVP_MD_CTX_get0_md(const EVP_MD_CTX *context);
const EVP_MD *EVP_MD_CTX_md(const EVP_MD_CTX *context);

int EVP_Digest(
    const void *data,
    size_t length,
    unsigned char *output,
    unsigned int *output_length,
    const EVP_MD *digest,
    void *engine
);

#ifdef __cplusplus
}
#endif

#endif
