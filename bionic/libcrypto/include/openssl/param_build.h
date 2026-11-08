#ifndef MYLINUX_OPENSSL_PARAM_BUILD_H
#define MYLINUX_OPENSSL_PARAM_BUILD_H

#include <stddef.h>
#include <openssl/params.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ossl_param_bld_st OSSL_PARAM_BLD;

OSSL_PARAM_BLD *OSSL_PARAM_BLD_new(void);
void OSSL_PARAM_BLD_free(OSSL_PARAM_BLD *);

int OSSL_PARAM_BLD_push_int(OSSL_PARAM_BLD *, const char *, int);
int OSSL_PARAM_BLD_push_uint(OSSL_PARAM_BLD *, const char *, unsigned int);
int OSSL_PARAM_BLD_push_size_t(OSSL_PARAM_BLD *, const char *, size_t);
int OSSL_PARAM_BLD_push_utf8_string(
    OSSL_PARAM_BLD *, const char *, const char *, size_t);
int OSSL_PARAM_BLD_push_octet_string(
    OSSL_PARAM_BLD *, const char *, const void *, size_t);

OSSL_PARAM *OSSL_PARAM_BLD_to_param(OSSL_PARAM_BLD *);

#ifdef __cplusplus
}
#endif

#endif
