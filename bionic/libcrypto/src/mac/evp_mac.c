#include <stdlib.h>
#include <string.h>

#include <openssl/evp_mac.h>
#include "evp_mac_internal.h"

static const EVP_MAC hmac_descriptor = {
    "HMAC", 1
};

const EVP_MAC *EVP_MAC_fetch(
    void *library_context,
    const char *algorithm,
    const char *properties)
{
    (void)library_context;
    (void)properties;

    if (algorithm == NULL)
        return NULL;

    if (strcmp(algorithm, "HMAC") != 0)
        return NULL;

    return &hmac_descriptor;
}

EVP_MAC_CTX *EVP_MAC_CTX_new(const EVP_MAC *mac)
{
    if (mac == NULL)
        return NULL;

    EVP_MAC_CTX *context = calloc(1, sizeof(*context));

    if (context == NULL)
        return NULL;

    context->mac = mac;
    context->state = EVP_MAC_STATE_EMPTY;

    return context;
}

void EVP_MAC_CTX_free(EVP_MAC_CTX *context)
{
    if (context == NULL)
        return;

    memset(context, 0, sizeof(*context));
    free(context);
}

int EVP_MAC_init(
    EVP_MAC_CTX *context,
    const unsigned char *key,
    size_t key_length,
    const void *parameters)
{
    (void)key;
    (void)key_length;
    (void)parameters;

    if (context == NULL)
        return 0;

    context->state = EVP_MAC_STATE_FAILED;
    return 0;
}

int EVP_MAC_update(
    EVP_MAC_CTX *context,
    const unsigned char *data,
    size_t data_length)
{
    (void)data;
    (void)data_length;

    if (context == NULL)
        return 0;

    return 0;
}

int EVP_MAC_final(
    EVP_MAC_CTX *context,
    unsigned char *output,
    size_t *output_length,
    size_t output_size)
{
    (void)output;
    (void)output_size;

    if (output_length != NULL)
        *output_length = 0;

    if (context == NULL)
        return 0;

    return 0;
}

size_t EVP_MAC_CTX_get_mac_size(const EVP_MAC_CTX *context)
{
    (void)context;

    return 0;
}
