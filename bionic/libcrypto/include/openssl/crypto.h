#ifndef MYLIBCRYPTO_OPENSSL_CRYPTO_H
#define MYLIBCRYPTO_OPENSSL_CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

#define OPENSSL_VERSION_TEXT "MyLinux libcrypto compatibility"

const char *OpenSSL_version(int type);

#ifdef __cplusplus
}
#endif

#endif
