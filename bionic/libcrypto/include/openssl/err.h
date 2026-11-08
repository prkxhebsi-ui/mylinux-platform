#ifndef MYLIBCRYPTO_OPENSSL_ERR_H
#define MYLIBCRYPTO_OPENSSL_ERR_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long ERR_get_error(void);
unsigned long ERR_peek_error(void);
void ERR_clear_error(void);
void ERR_error_string_n(
    unsigned long error,
    char *buffer,
    unsigned long length
);

#ifdef __cplusplus
}
#endif

#endif
