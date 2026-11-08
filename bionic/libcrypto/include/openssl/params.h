#ifndef MYLINUX_OPENSSL_PARAMS_H
#define MYLINUX_OPENSSL_PARAMS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ossl_param_st {
    const char *key;
    unsigned int data_type;
    void *data;
    size_t data_size;
    size_t return_size;
} OSSL_PARAM;

#define OSSL_PARAM_END \
    { NULL, 0U, NULL, 0U, 0U }

#define OSSL_PARAM_INTEGER       1U
#define OSSL_PARAM_UNSIGNED_INTEGER 2U
#define OSSL_PARAM_REAL          3U
#define OSSL_PARAM_UTF8_STRING   4U
#define OSSL_PARAM_OCTET_STRING  5U
#define OSSL_PARAM_UTF8_PTR      6U
#define OSSL_PARAM_OCTET_PTR     7U

#define OSSL_PARAM_DEFN(k, t, d, s) \
    { (k), (t), (d), (s), 0U }

#define OSSL_PARAM_int(k, p) \
    OSSL_PARAM_DEFN((k), OSSL_PARAM_INTEGER, (p), sizeof(int))

#define OSSL_PARAM_uint(k, p) \
    OSSL_PARAM_DEFN((k), OSSL_PARAM_UNSIGNED_INTEGER, (p), sizeof(unsigned int))

#define OSSL_PARAM_size_t(k, p) \
    OSSL_PARAM_DEFN((k), OSSL_PARAM_UNSIGNED_INTEGER, (p), sizeof(size_t))

#define OSSL_PARAM_utf8_string(k, p, s) \
    OSSL_PARAM_DEFN((k), OSSL_PARAM_UTF8_STRING, (p), (s))

#define OSSL_PARAM_octet_string(k, p, s) \
    OSSL_PARAM_DEFN((k), OSSL_PARAM_OCTET_STRING, (p), (s))

OSSL_PARAM OSSL_PARAM_construct_end(void);
OSSL_PARAM OSSL_PARAM_construct_int(const char *, int *);
OSSL_PARAM OSSL_PARAM_construct_uint(const char *, unsigned int *);
OSSL_PARAM OSSL_PARAM_construct_size_t(const char *, size_t *);
OSSL_PARAM OSSL_PARAM_construct_utf8_string(const char *, char *, size_t);
OSSL_PARAM OSSL_PARAM_construct_octet_string(const char *, void *, size_t);

OSSL_PARAM *OSSL_PARAM_locate(OSSL_PARAM *, const char *);
const OSSL_PARAM *OSSL_PARAM_locate_const(const OSSL_PARAM *, const char *);

int OSSL_PARAM_get_int(const OSSL_PARAM *, int *);
int OSSL_PARAM_get_uint(const OSSL_PARAM *, unsigned int *);
int OSSL_PARAM_get_size_t(const OSSL_PARAM *, size_t *);
int OSSL_PARAM_get_utf8_string(const OSSL_PARAM *, char **, size_t);
int OSSL_PARAM_get_octet_string(const OSSL_PARAM *, void **, size_t, size_t *);

int OSSL_PARAM_set_int(OSSL_PARAM *, int);
int OSSL_PARAM_set_uint(OSSL_PARAM *, unsigned int);
int OSSL_PARAM_set_size_t(OSSL_PARAM *, size_t);
int OSSL_PARAM_set_utf8_string(OSSL_PARAM *, const char *);
int OSSL_PARAM_set_octet_string(OSSL_PARAM *, const void *, size_t);

#ifdef __cplusplus
}
#endif

#endif
