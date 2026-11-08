#ifndef MYLIBCRYPTO_OPENSSL_CRYPTO_EX_H
#define MYLIBCRYPTO_OPENSSL_CRYPTO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

int CRYPTO_library_init(void);
const char *CRYPTO_library_name(void);
unsigned long CRYPTO_library_version(void);

#ifdef __cplusplus
}
#endif

#endif
