#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/evp_ex.h>

int main(void)
{
    EVP_MD_CTX *context = EVP_MD_CTX_new();

    if (context == NULL) {
        fprintf(stderr, "EVP_MD_CTX_new failed\n");
        return 1;
    }

    const EVP_MD *sha256 = EVP_sha256();
    const EVP_MD *sha512 = EVP_sha512();

    if (sha256 == NULL || sha512 == NULL) {
        fprintf(stderr, "Digest descriptors unavailable\n");
        EVP_MD_CTX_free(context);
        return 1;
    }

    if (EVP_MD_size(sha256) != 32 ||
        EVP_MD_size(sha512) != 64) {
        fprintf(stderr, "Incorrect digest metadata\n");
        EVP_MD_CTX_free(context);
        return 1;
    }

    if (EVP_MD_CTX_reset(context) != 1) {
        fprintf(stderr, "Context reset failed\n");
        EVP_MD_CTX_free(context);
        return 1;
    }

    EVP_MD_CTX_free(context);

    puts("EVP API metadata and lifecycle tests passed.");
    puts("Digest computation is not yet implemented.");

    return 0;
}
