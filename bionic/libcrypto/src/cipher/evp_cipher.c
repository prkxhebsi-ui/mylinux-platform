#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/evp_cipher.h>

#include "evp_cipher_internal.h"

static const EVP_CIPHER aes128cbc = {
    "AES-128-CBC", 16, 16, 16, EVP_CIPHER_MODE_CBC
};

static const EVP_CIPHER aes192cbc = {
    "AES-192-CBC", 24, 16, 16, EVP_CIPHER_MODE_CBC
};

static const EVP_CIPHER aes256cbc = {
    "AES-256-CBC", 32, 16, 16, EVP_CIPHER_MODE_CBC
};

const EVP_CIPHER *EVP_aes_128_cbc(void)
{
    return &aes128cbc;
}

const EVP_CIPHER *EVP_aes_192_cbc(void)
{
    return &aes192cbc;
}

const EVP_CIPHER *EVP_aes_256_cbc(void)
{
    return &aes256cbc;
}

EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void)
{
    EVP_CIPHER_CTX *context = calloc(1, sizeof(*context));

    if (context == NULL)
        return NULL;

    context->state = EVP_CIPHER_STATE_EMPTY;
    context->padding = 1;

    return context;
}

void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *context)
{
    if (context == NULL)
        return;

    memset(context, 0, sizeof(*context));
    free(context);
}

int EVP_CIPHER_CTX_reset(EVP_CIPHER_CTX *context)
{
    if (context == NULL)
        return 0;

    memset(context, 0, sizeof(*context));
    context->state = EVP_CIPHER_STATE_EMPTY;
    context->padding = 1;

    return 1;
}

int EVP_CIPHER_get_key_length(const EVP_CIPHER *cipher)
{
    return cipher == NULL ? 0 : (int)cipher->key_length;
}

int EVP_CIPHER_get_iv_length(const EVP_CIPHER *cipher)
{
    return cipher == NULL ? 0 : (int)cipher->iv_length;
}

int EVP_CIPHER_get_block_size(const EVP_CIPHER *cipher)
{
    return cipher == NULL ? 0 : (int)cipher->block_size;
}

int EVP_CIPHER_CTX_set_padding(
    EVP_CIPHER_CTX *context,
    int padding)
{
    if (context == NULL || (padding != 0 && padding != 1))
        return 0;

    if (context->state != EVP_CIPHER_STATE_EMPTY)
        return 0;

    context->padding = padding;
    return 1;
}
