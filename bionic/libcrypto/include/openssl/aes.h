#ifndef MYLIBCRYPTO_OPENSSL_AES_H
#define MYLIBCRYPTO_OPENSSL_AES_H

#define AES_BLOCK_SIZE 16
#define AES_MAXNR 14

typedef struct aes_key_st {
    unsigned int rd_key[4 * (AES_MAXNR + 1)];
    int rounds;
} AES_KEY;

#endif
