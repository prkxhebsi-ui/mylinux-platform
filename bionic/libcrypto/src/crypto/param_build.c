#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/param_build.h>
#include "param_build_internal.h"

static int reserve(OSSL_PARAM_BLD *b)
{
    size_t cap;
    struct ossl_param_bld_entry_st *p;

    if (b->count < b->capacity)
        return 1;

    cap = b->capacity ? b->capacity * 2 : 8;
    if (cap < b->capacity ||
        cap > SIZE_MAX / sizeof(*p))
        return 0;

    p = realloc(b->entries, cap * sizeof(*p));
    if (!p)
        return 0;

    b->entries = p;
    b->capacity = cap;
    return 1;
}

OSSL_PARAM_BLD *OSSL_PARAM_BLD_new(void)
{
    return calloc(1, sizeof(OSSL_PARAM_BLD));
}

void OSSL_PARAM_BLD_free(OSSL_PARAM_BLD *b)
{
    size_t i;
    if (!b)
        return;

    for (i = 0; i < b->count; ++i) {
        free(b->entries[i].key);
        free(b->entries[i].data);
    }
    free(b->entries);
    free(b);
}

static int push(OSSL_PARAM_BLD *b, const char *key,
                unsigned int type, const void *data, size_t size)
{
    struct ossl_param_bld_entry_st *e;

    if (!b || !key || !*key || (!data && size))
        return 0;

    if (!reserve(b))
        return 0;

    e = &b->entries[b->count];
    memset(e, 0, sizeof(*e));

    e->key = strdup(key);
    e->data = size ? malloc(size) : NULL;
    if (!e->key || (size && !e->data)) {
        free(e->key);
        free(e->data);
        memset(e, 0, sizeof(*e));
        return 0;
    }

    if (size)
        memcpy(e->data, data, size);

    e->type = type;
    e->size = size;
    ++b->count;
    return 1;
}

int OSSL_PARAM_BLD_push_int(OSSL_PARAM_BLD *b, const char *k, int v)
{
    return push(b, k, OSSL_PARAM_INTEGER, &v, sizeof(v));
}

int OSSL_PARAM_BLD_push_uint(
    OSSL_PARAM_BLD *b, const char *k, unsigned int v)
{
    return push(b, k, OSSL_PARAM_UNSIGNED_INTEGER, &v, sizeof(v));
}

int OSSL_PARAM_BLD_push_size_t(OSSL_PARAM_BLD *b, const char *k, size_t v)
{
    return push(b, k, OSSL_PARAM_UNSIGNED_INTEGER, &v, sizeof(v));
}

int OSSL_PARAM_BLD_push_utf8_string(
    OSSL_PARAM_BLD *b, const char *k, const char *v, size_t n)
{
    if (!v)
        return 0;
    if (n == 0)
        n = strlen(v) + 1;
    return push(b, k, OSSL_PARAM_UTF8_STRING, v, n);
}

int OSSL_PARAM_BLD_push_octet_string(
    OSSL_PARAM_BLD *b, const char *k, const void *v, size_t n)
{
    return push(b, k, OSSL_PARAM_OCTET_STRING, v, n);
}

OSSL_PARAM *OSSL_PARAM_BLD_to_param(OSSL_PARAM_BLD *b)
{
    OSSL_PARAM *params;
    size_t i;

    if (!b || b->count == SIZE_MAX ||
        b->count + 1 > SIZE_MAX / sizeof(*params))
        return NULL;

    params = calloc(b->count + 1, sizeof(*params));
    if (!params)
        return NULL;

    for (i = 0; i < b->count; ++i) {
        params[i].key = strdup(b->entries[i].key);
        params[i].data = b->entries[i].size
            ? malloc(b->entries[i].size) : NULL;

        if (!params[i].key ||
            (b->entries[i].size && !params[i].data)) {
            OSSL_PARAM *p;
            for (p = params; p <= &params[i]; ++p) {
                free((void *)p->key);
                free(p->data);
            }
            free(params);
            return NULL;
        }

        if (b->entries[i].size)
            memcpy(params[i].data, b->entries[i].data,
                   b->entries[i].size);

        params[i].data_type = b->entries[i].type;
        params[i].data_size = b->entries[i].size;
    }

    return params;
}
