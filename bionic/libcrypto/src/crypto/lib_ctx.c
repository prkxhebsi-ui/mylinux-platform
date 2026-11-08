#include <stdlib.h>
#include "lib_ctx_internal.h"

static struct ossl_lib_ctx_st global_context;

OSSL_LIB_CTX *OSSL_LIB_CTX_new(void)
{
    return calloc(1, sizeof(OSSL_LIB_CTX));
}

void OSSL_LIB_CTX_free(OSSL_LIB_CTX *ctx)
{
    if (ctx && ctx != &global_context)
        free(ctx);
}

OSSL_LIB_CTX *OSSL_LIB_CTX_get0_global_default(void)
{
    return &global_context;
}

OSSL_LIB_CTX *OSSL_LIB_CTX_set0_default(OSSL_LIB_CTX *ctx)
{
    (void)ctx;
    return NULL;
}
