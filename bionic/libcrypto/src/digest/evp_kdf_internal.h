#ifndef MYLIBCRYPTO_EVP_KDF_INTERNAL_H
#define MYLIBCRYPTO_EVP_KDF_INTERNAL_H

#include <stddef.h>
#include <openssl/kdf.h>

#define EVP_KDF_STATE_EMPTY 0
#define EVP_KDF_STATE_FAILED 1

struct evp_kdf_st {
    const char *name;
    unsigned int identifier;
};

struct evp_kdf_ctx_st {
    const EVP_KDF *kdf;
    unsigned int state;
};

#endif
