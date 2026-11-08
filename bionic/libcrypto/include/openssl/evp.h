#ifndef MYLIBCRYPTO_OPENSSL_EVP_H
#define MYLIBCRYPTO_OPENSSL_EVP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct evp_md_st EVP_MD;
typedef struct evp_md_ctx_st EVP_MD_CTX;
typedef struct evp_cipher_st EVP_CIPHER;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;

const EVP_MD *EVP_sha256(void);
const EVP_MD *EVP_sha512(void);

EVP_MD_CTX *EVP_MD_CTX_new(void);
void EVP_MD_CTX_free(EVP_MD_CTX *context);

int EVP_DigestInit_ex(
    EVP_MD_CTX *context,
    const EVP_MD *digest,
    void *engine
);

int EVP_DigestUpdate(
    EVP_MD_CTX *context,
    const void *data,
    size_t length
);

int EVP_DigestFinal_ex(
    EVP_MD_CTX *context,
    unsigned char *output,
    unsigned int *output_length
);

#ifdef __cplusplus
}
#endif

#endif
