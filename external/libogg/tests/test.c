#include "ogg/ogg.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    unsigned char data[28] = {0};
    memcpy(data, "OggS", 4);

    data[4] = 0;
    data[26] = 1;
    data[27] = 0;

    ogg_page page;

    int result = ogg_page_parse(data, sizeof(data), &page);

    printf("%s\n", ogg_version());

    if (result != 0) {
        printf("Parser error: %d\n", result);
        return 1;
    }

    printf("Ogg page parsed successfully\n");
    printf("Version: %u\n", page.version);
    printf("Segments: %u\n", page.segment_count);
    printf("Body size: %zu\n", page.body_size);

    return 0;
}
