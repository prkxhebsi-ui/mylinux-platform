#ifndef MYLINUX_DIVSUFSORT_H
#define MYLINUX_DIVSUFSORT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char sauchar_t;
typedef int32_t saidx_t;

int divsufsort(
    const sauchar_t *text,
    saidx_t *suffix_array,
    saidx_t length
);

const char *divsufsort_version(void);

#ifdef __cplusplus
}
#endif

#endif
