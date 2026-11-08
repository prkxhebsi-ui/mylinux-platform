#include <stdio.h>

#include <openssl/evp.h>
#include <openssl/evp_cipher.h>

int main(void)
{
    const EVP_CIPHER *aes128 = EVP_aes_128_cbc();
    const EVP_CIPHER *aes192 = EVP_aes_192_cbc();
    const EVP_CIPHER *aes256 = EVP_aes_256_cbc();

    if (aes128 == NULL || aes192 == NULL || aes256 == NULL) {
        fprintf(stderr, "Cipher descriptors unavailable\n");
        return 1;
    }

    if (EVP_CIPHER_get_key_length(aes128) != 16 ||
        EVP_CIPHER_get_key_length(aes192) != 24 ||
        EVP_CIPHER_get_key_length(aes256) != 32) {
        fprintf(stderr, "Incorrect AES key metadata\n");
        return 1;
    }

    if (EVP_CIPHER_get_iv_length(aes256) != 16 ||
        EVP_CIPHER_get_block_size(aes256) != 16) {
        fprintf(stderr, "Incorrect AES block metadata\n");
        return 1;
    }

    EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();

    if (context == NULL) {
        fprintf(stderr, "Cipher context allocation failed\n");
        return 1;
    }

    if (!EVP_CIPHER_CTX_set_padding(context, 0)) {
        fprintf(stderr, "Padding configuration failed\n");
        EVP_CIPHER_CTX_free(context);
        return 1;
    }

    if (!EVP_CIPHER_CTX_reset(context)) {
        fprintf(stderr, "Context reset failed\n");
        EVP_CIPHER_CTX_free(context);
        return 1;
    }

    EVP_CIPHER_CTX_free(context);

    puts("EVP cipher metadata and lifecycle tests passed.");
    puts("AES encryption/decryption backend remains pending.");

    return 0;
}
