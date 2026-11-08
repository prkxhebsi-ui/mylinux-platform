#include "divsufsort.h"

#include <stdio.h>

int main(void) {
    const sauchar_t text[] = "banana";
    const saidx_t length = 6;
    saidx_t sa[6];

    int result = divsufsort(text, sa, length);

    if (result != 0) {
        printf("Suffix array failed: %d\n", result);
        return 1;
    }

    printf("%s\n", divsufsort_version());
    printf("Suffix array: ");

    for (saidx_t i = 0; i < length; i++)
        printf("%d ", sa[i]);

    putchar('\n');
    return 0;
}
