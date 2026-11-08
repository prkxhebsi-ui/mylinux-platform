#ifndef MYLIBCRYPTO_OPENSSL_RAND_H
#define MYLIBCRYPTO_OPENSSL_RAND_H

#ifdef __cplusplus
extern "C" {
#endif

int RAND_bytes(unsigned char *buffer, int length);
int RAND_priv_bytes(unsigned char *buffer, int length);

#ifdef __cplusplus
}
#endif

#endif
