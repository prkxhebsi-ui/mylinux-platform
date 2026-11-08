#ifndef MYLINUX_PARAM_BUILD_INTERNAL_H
#define MYLINUX_PARAM_BUILD_INTERNAL_H

#include <stddef.h>
#include <openssl/param_build.h>

struct ossl_param_bld_entry_st {
    char *key;
    unsigned int type;
    void *data;
    size_t size;
};

struct ossl_param_bld_st {
    struct ossl_param_bld_entry_st *entries;
    size_t count;
    size_t capacity;
};

#endif
