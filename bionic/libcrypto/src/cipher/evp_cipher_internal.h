#ifndef MYLIBCRYPTO_EVP_CIPHER_INTERNAL_H
#define MYLIBCRYPTO_EVP_CIPHER_INTERNAL_H

#include <openssl/evp.h>

#define EVP_CIPHER_MODE_CBC 1

#define EVP_CIPHER_STATE_EMPTY 0
#define EVP_CIPHER_STATE_ENCRYPT 1
#define EVP_CIPHER_STATE_DECRYPT 2
#define EVP_CIPHER_STATE_FAILED 3

struct evp_cipher_st {
    const char *name;
    unsigned int key_length;
    unsigned int iv_length;
    unsigned int block_size;
    unsigned int mode;
};

struct evp_cipher_ctx_st {
    const EVP_CIPHER *cipher;
    unsigned int state;
    int padding;
};

#endif
