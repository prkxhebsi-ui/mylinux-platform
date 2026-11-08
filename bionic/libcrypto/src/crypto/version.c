#include <openssl/crypto_ex.h>
#include <openssl/opensslv.h>

int CRYPTO_library_init(void)
{
    return 1;
}

const char *CRYPTO_library_name(void)
{
    return "MyLinux libcrypto";
}

unsigned long CRYPTO_library_version(void)
{
    return OPENSSL_VERSION_NUMBER;
}
