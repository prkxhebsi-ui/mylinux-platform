#include <openssl/evp_cipher.h>

#include "evp_cipher_internal.h"

/*
 * Encryption and decryption are intentionally disabled.
 *
 * These functions must be connected to a reviewed AES-CBC backend.
 * They must not produce fabricated ciphertext or plaintext.
 */

static int unavailable(EVP_CIPHER_CTX *context, int *output_length)
{
    if (output_length != NULL)
        *output_length = 0;

    if (context != NULL)
        context->state = EVP_CIPHER_STATE_FAILED;

    return 0;
}

int EVP_EncryptInit_ex(
    EVP_CIPHER_CTX *context,
    const EVP_CIPHER *cipher,
    void *engine,
    const unsigned char *key,
    const unsigned char *iv)
{
    (void)engine;
    (void)key;
    (void)iv;

    if (context == NULL || cipher == NULL)
        return 0;

    return unavailable(context, NULL);
}

int EVP_EncryptUpdate(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length,
    const unsigned char *input,
    int input_length)
{
    (void)output;
    (void)input;
    (void)input_length;

    return unavailable(context, output_length);
}

int EVP_EncryptFinal_ex(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length)
{
    (void)output;

    return unavailable(context, output_length);
}

int EVP_DecryptInit_ex(
    EVP_CIPHER_CTX *context,
    const EVP_CIPHER *cipher,
    void *engine,
    const unsigned char *key,
    const unsigned char *iv)
{
    (void)engine;
    (void)key;
    (void)iv;

    if (context == NULL || cipher == NULL)
        return 0;

    return unavailable(context, NULL);
}

int EVP_DecryptUpdate(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length,
    const unsigned char *input,
    int input_length)
{
    (void)output;
    (void)input;
    (void)input_length;

    return unavailable(context, output_length);
}

int EVP_DecryptFinal_ex(
    EVP_CIPHER_CTX *context,
    unsigned char *output,
    int *output_length)
{
    (void)output;

    return unavailable(context, output_length);
}
