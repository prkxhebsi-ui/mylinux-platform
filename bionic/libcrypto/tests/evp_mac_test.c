#include <stdio.h>

#include <openssl/evp_mac.h>
#include <openssl/kdf.h>

int main(void)
{
    const EVP_MAC *mac = EVP_MAC_fetch(NULL, "HMAC", NULL);
    const EVP_KDF *kdf = EVP_KDF_fetch(NULL, "HKDF", NULL);

    if (mac == NULL || kdf == NULL) {
        fprintf(stderr, "MAC/KDF descriptors unavailable\n");
        return 1;
    }

    EVP_MAC_CTX *mac_context = EVP_MAC_CTX_new(mac);
    EVP_KDF_CTX *kdf_context = EVP_KDF_CTX_new(kdf);

    if (mac_context == NULL || kdf_context == NULL) {
        fprintf(stderr, "Context allocation failed\n");
        EVP_MAC_CTX_free(mac_context);
        EVP_KDF_CTX_free(kdf_context);
        return 1;
    }

    EVP_MAC_CTX_free(mac_context);
    EVP_KDF_CTX_free(kdf_context);

    puts("EVP MAC/KDF metadata and lifecycle tests passed.");
    puts("Cryptographic operations remain pending.");

    return 0;
}
