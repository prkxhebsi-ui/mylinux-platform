#include "divsufsort.h"

#include <stdlib.h>
#include <string.h>

static const saidx_t *g_rank;
static saidx_t g_length;
static saidx_t g_offset;

static int compare_suffixes(const void *a, const void *b) {
    saidx_t x = *(const saidx_t *)a;
    saidx_t y = *(const saidx_t *)b;

    if (g_rank[x] != g_rank[y])
        return (g_rank[x] > g_rank[y]) - (g_rank[x] < g_rank[y]);

    saidx_t rx = x + g_offset < g_length
        ? g_rank[x + g_offset] : -1;

    saidx_t ry = y + g_offset < g_length
        ? g_rank[y + g_offset] : -1;

    return (rx > ry) - (rx < ry);
}

const char *divsufsort_version(void) {
    return "MyLinux libdivsufsort 1.0";
}

int divsufsort(
    const sauchar_t *text,
    saidx_t *suffix_array,
    saidx_t length
) {
    if (length < 0 || (!text && length) ||
        (!suffix_array && length))
        return -1;

    if (length == 0)
        return 0;

    saidx_t *rank = malloc((size_t)length * sizeof(*rank));
    saidx_t *next_rank = malloc((size_t)length * sizeof(*next_rank));

    if (!rank || !next_rank) {
        free(rank);
        free(next_rank);
        return -2;
    }

    for (saidx_t i = 0; i < length; i++) {
        suffix_array[i] = i;
        rank[i] = text[i];
    }

    for (saidx_t width = 1; width < length; ) {
        g_rank = rank;
        g_length = length;
        g_offset = width;

        qsort(
            suffix_array,
            (size_t)length,
            sizeof(*suffix_array),
            compare_suffixes
        );

        next_rank[suffix_array[0]] = 0;

        for (saidx_t i = 1; i < length; i++) {
            saidx_t a = suffix_array[i - 1];
            saidx_t b = suffix_array[i];

            int different = rank[a] != rank[b];

            saidx_t a2 = a + width < length
                ? rank[a + width] : -1;

            saidx_t b2 = b + width < length
                ? rank[b + width] : -1;

            if (a2 != b2)
                different = 1;

            next_rank[b] = next_rank[a] + different;
        }

        memcpy(rank, next_rank, (size_t)length * sizeof(*rank));

        if (rank[suffix_array[length - 1]] == length - 1)
            break;

        if (width > length / 2)
            break;

        width *= 2;
    }

    free(rank);
    free(next_rank);
    return 0;
}
