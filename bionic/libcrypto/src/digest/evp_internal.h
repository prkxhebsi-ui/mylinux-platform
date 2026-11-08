#ifndef MYLIBCRYPTO_EVP_INTERNAL_H
#define MYLIBCRYPTO_EVP_INTERNAL_H

#include <stddef.h>
#include <openssl/evp.h>

#define EVP_INTERNAL_STATE_EMPTY 0
#define EVP_INTERNAL_STATE_INITIALIZED 1
#define EVP_INTERNAL_STATE_FAILED 2

struct evp_md_st {
    const char *name;
    unsigned int digest_size;
    unsigned int block_size;
    unsigned int identifier;
};

struct evp_md_ctx_st {
    const EVP_MD *digest;
    unsigned int state;
};

#endif
