#include <stdlib.h>
#include <string.h>

#include <openssl/kdf.h>
#include "evp_kdf_internal.h"

static const EVP_KDF hkdf_descriptor = {
    "HKDF", 1
};

const EVP_KDF *EVP_KDF_fetch(
    void *library_context,
    const char *algorithm,
    const char *properties)
{
    (void)library_context;
    (void)properties;

    if (algorithm == NULL)
        return NULL;

    if (strcmp(algorithm, "HKDF") != 0)
        return NULL;

    return &hkdf_descriptor;
}

EVP_KDF_CTX *EVP_KDF_CTX_new(const EVP_KDF *kdf)
{
    if (kdf == NULL)
        return NULL;

    EVP_KDF_CTX *context = calloc(1, sizeof(*context));

    if (context == NULL)
        return NULL;

    context->kdf = kdf;
    context->state = EVP_KDF_STATE_EMPTY;

    return context;
}

void EVP_KDF_CTX_free(EVP_KDF_CTX *context)
{
    if (context == NULL)
        return;

    memset(context, 0, sizeof(*context));
    free(context);
}

int EVP_KDF_derive(
    EVP_KDF_CTX *context,
    unsigned char *output,
    size_t output_length,
    const void *parameters)
{
    (void)output;
    (void)output_length;
    (void)parameters;

    if (context == NULL)
        return 0;

    context->state = EVP_KDF_STATE_FAILED;
    return 0;
}
