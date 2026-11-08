#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/evp_ex.h>

#include "evp_internal.h"

static const EVP_MD sha256_descriptor = {
    "SHA256", 32, 64, 1
};

static const EVP_MD sha512_descriptor = {
    "SHA512", 64, 128, 2
};

const EVP_MD *EVP_sha256(void)
{
    return &sha256_descriptor;
}

const EVP_MD *EVP_sha512(void)
{
    return &sha512_descriptor;
}

EVP_MD_CTX *EVP_MD_CTX_new(void)
{
    EVP_MD_CTX *context = calloc(1, sizeof(*context));

    if (context == NULL)
        return NULL;

    context->state = EVP_INTERNAL_STATE_EMPTY;
    return context;
}

void EVP_MD_CTX_free(EVP_MD_CTX *context)
{
    if (context == NULL)
        return;

    memset(context, 0, sizeof(*context));
    free(context);
}

int EVP_MD_CTX_reset(EVP_MD_CTX *context)
{
    if (context == NULL)
        return 0;

    context->digest = NULL;
    context->state = EVP_INTERNAL_STATE_EMPTY;
    return 1;
}

int EVP_MD_get_size(const EVP_MD *digest)
{
    if (digest == NULL)
        return 0;

    return (int)digest->digest_size;
}

int EVP_MD_size(const EVP_MD *digest)
{
    return EVP_MD_get_size(digest);
}

const EVP_MD *EVP_MD_CTX_get0_md(const EVP_MD_CTX *context)
{
    if (context == NULL)
        return NULL;

    return context->digest;
}

const EVP_MD *EVP_MD_CTX_md(const EVP_MD_CTX *context)
{
    return EVP_MD_CTX_get0_md(context);
}

/*
 * These operations deliberately fail until a reviewed digest backend
 * has been integrated.
 */

int EVP_DigestInit_ex(
    EVP_MD_CTX *context,
    const EVP_MD *digest,
    void *engine)
{
    (void)engine;

    if (context == NULL || digest == NULL)
        return 0;

    context->digest = NULL;
    context->state = EVP_INTERNAL_STATE_FAILED;
    return 0;
}

int EVP_DigestUpdate(
    EVP_MD_CTX *context,
    const void *data,
    size_t length)
{
    (void)data;
    (void)length;

    if (context == NULL)
        return 0;

    return 0;
}

int EVP_DigestFinal_ex(
    EVP_MD_CTX *context,
    unsigned char *output,
    unsigned int *output_length)
{
    (void)output;

    if (output_length != NULL)
        *output_length = 0;

    if (context == NULL)
        return 0;

    return 0;
}

int EVP_Digest(
    const void *data,
    size_t length,
    unsigned char *output,
    unsigned int *output_length,
    const EVP_MD *digest,
    void *engine)
{
    (void)data;
    (void)length;
    (void)output;
    (void)digest;
    (void)engine;

    if (output_length != NULL)
        *output_length = 0;

    return 0;
}
