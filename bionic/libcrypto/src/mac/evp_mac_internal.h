#ifndef MYLIBCRYPTO_EVP_MAC_INTERNAL_H
#define MYLIBCRYPTO_EVP_MAC_INTERNAL_H

#include <stddef.h>
#include <openssl/evp_mac.h>

#define EVP_MAC_STATE_EMPTY 0
#define EVP_MAC_STATE_INITIALIZED 1
#define EVP_MAC_STATE_FAILED 2

struct evp_mac_st {
    const char *name;
    unsigned int identifier;
};

struct evp_mac_ctx_st {
    const EVP_MAC *mac;
    unsigned int state;
    size_t key_length;
};

#endif
