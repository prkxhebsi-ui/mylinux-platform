#include <string.h>
#include <stdlib.h>
#include <openssl/params.h>

OSSL_PARAM OSSL_PARAM_construct_end(void)
{
    OSSL_PARAM p = OSSL_PARAM_END;
    return p;
}

static OSSL_PARAM construct(
    const char *key, unsigned int type, void *data, size_t size)
{
    OSSL_PARAM p = { key, type, data, size, 0U };
    return p;
}

OSSL_PARAM OSSL_PARAM_construct_int(const char *k, int *v)
{
    return construct(k, OSSL_PARAM_INTEGER, v, sizeof(*v));
}

OSSL_PARAM OSSL_PARAM_construct_uint(const char *k, unsigned int *v)
{
    return construct(k, OSSL_PARAM_UNSIGNED_INTEGER, v, sizeof(*v));
}

OSSL_PARAM OSSL_PARAM_construct_size_t(const char *k, size_t *v)
{
    return construct(k, OSSL_PARAM_UNSIGNED_INTEGER, v, sizeof(*v));
}

OSSL_PARAM OSSL_PARAM_construct_utf8_string(
    const char *k, char *v, size_t n)
{
    return construct(k, OSSL_PARAM_UTF8_STRING, v, n);
}

OSSL_PARAM OSSL_PARAM_construct_octet_string(
    const char *k, void *v, size_t n)
{
    return construct(k, OSSL_PARAM_OCTET_STRING, v, n);
}

OSSL_PARAM *OSSL_PARAM_locate(OSSL_PARAM *p, const char *key)
{
    if (!p || !key)
        return NULL;

    for (; p->key; ++p) {
        if (strcmp(p->key, key) == 0)
            return p;
    }
    return NULL;
}

const OSSL_PARAM *OSSL_PARAM_locate_const(
    const OSSL_PARAM *p, const char *key)
{
    if (!p || !key)
        return NULL;

    for (; p->key; ++p) {
        if (strcmp(p->key, key) == 0)
            return p;
    }
    return NULL;
}

static int copy_out(const OSSL_PARAM *p, unsigned int type,
                    void *out, size_t size)
{
    if (!p || !out || p->data_type != type ||
        !p->data || p->data_size != size)
        return 0;

    memcpy(out, p->data, size);
    return 1;
}

static int copy_in(OSSL_PARAM *p, unsigned int type,
                   const void *in, size_t size)
{
    if (!p || !in || p->data_type != type ||
        !p->data || p->data_size < size)
        return 0;

    memcpy(p->data, in, size);
    p->return_size = size;
    return 1;
}

int OSSL_PARAM_get_int(const OSSL_PARAM *p, int *v)
{
    return copy_out(p, OSSL_PARAM_INTEGER, v, sizeof(*v));
}

int OSSL_PARAM_get_uint(const OSSL_PARAM *p, unsigned int *v)
{
    return copy_out(p, OSSL_PARAM_UNSIGNED_INTEGER, v, sizeof(*v));
}

int OSSL_PARAM_get_size_t(const OSSL_PARAM *p, size_t *v)
{
    return copy_out(p, OSSL_PARAM_UNSIGNED_INTEGER, v, sizeof(*v));
}

int OSSL_PARAM_get_utf8_string(
    const OSSL_PARAM *p, char **out, size_t max_len)
{
    if (!p || !out || !*out ||
        p->data_type != OSSL_PARAM_UTF8_STRING ||
        !p->data || p->data_size == 0 ||
        max_len < p->data_size)
        return 0;

    memcpy(*out, p->data, p->data_size);
    return 1;
}

int OSSL_PARAM_get_octet_string(
    const OSSL_PARAM *p, void **out, size_t max_len, size_t *used)
{
    if (!p || !out || !*out ||
        p->data_type != OSSL_PARAM_OCTET_STRING ||
        !p->data || max_len < p->data_size)
        return 0;

    memcpy(*out, p->data, p->data_size);
    if (used)
        *used = p->data_size;
    return 1;
}

int OSSL_PARAM_set_int(OSSL_PARAM *p, int v)
{
    return copy_in(p, OSSL_PARAM_INTEGER, &v, sizeof(v));
}

int OSSL_PARAM_set_uint(OSSL_PARAM *p, unsigned int v)
{
    return copy_in(p, OSSL_PARAM_UNSIGNED_INTEGER, &v, sizeof(v));
}

int OSSL_PARAM_set_size_t(OSSL_PARAM *p, size_t v)
{
    return copy_in(p, OSSL_PARAM_UNSIGNED_INTEGER, &v, sizeof(v));
}

int OSSL_PARAM_set_utf8_string(OSSL_PARAM *p, const char *v)
{
    size_t n;
    if (!v)
        return 0;
    n = strlen(v) + 1;
    return copy_in(p, OSSL_PARAM_UTF8_STRING, v, n);
}

int OSSL_PARAM_set_octet_string(
    OSSL_PARAM *p, const void *v, size_t n)
{
    return copy_in(p, OSSL_PARAM_OCTET_STRING, v, n);
}
