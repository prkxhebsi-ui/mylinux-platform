#ifndef MYLIBCRYPTO_OPENSSL_EVP_CIPHER_H
#define MYLIBCRYPTO_OPENSSL_EVP_CIPHER_H

#include <stddef.h>
#include <openssl/evp.h>

#ifdef __cplusplus
extern "C" {
#endif

const EVP_CIPHER *EVP_aes_128_cbc(void);
const EVP_CIPHER *EVP_aes_192_cbc(void);
const EVP_CIPHER *EVP_aes_256_cbc(void);

EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void);
void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *context);
int EVP_CIPHER_CTX_reset(EVP_CIPHER_CTX *context);

int EVP_CIPHER_get_key_length(const EVP_CIPHER *cipher);
int EVP_CIPHER_get_iv_length(const EVP_CIPHER *cipher);
int EVP_CIPHER_get_block_size(const EVP_CIPHER *cipher);

int EVP_CIPHER_CTX_set_padding(
    EVP_CIPHER_CTX *context,
    int padding
);

int EVP_EncryptInit_ex(
    EVP_CIPHER_CTX *context,
    const EVP_CIPHER *cipher,
    void *engine,
    const unsigned char *key,
    const unsigned char *iv
);

int EVP_EncryptUpdate(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length,
    const unsigned char *input,
    int input_length
);

int EVP_EncryptFinal_ex(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length
);

int EVP_DecryptInit_ex(
    EVP_CIPHER_CTX *context,
    const EVP_CIPHER *cipher,
    void *engine,
    const unsigned char *key,
    const unsigned char *iv
);

int EVP_DecryptUpdate(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length,
    const unsigned char *input,
    int input_length
);

int EVP_DecryptFinal_ex(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length
);

#ifdef __cplusplus
}
#endif

#endif
