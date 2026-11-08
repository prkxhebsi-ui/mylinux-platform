#ifndef MYLINUX_LIB_CTX_INTERNAL_H
#define MYLINUX_LIB_CTX_INTERNAL_H

#include <stddef.h>

struct ossl_lib_ctx_st {
    unsigned int flags;
    void *provider_store;
};

#endif
