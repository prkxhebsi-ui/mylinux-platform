#include <stdio.h>
#include <openssl/sha.h>

int main(void)
{
    unsigned char output[SHA256_DIGEST_LENGTH];

    (void)output;

    puts("SHA-256 API declaration test");
    return 0;
}
