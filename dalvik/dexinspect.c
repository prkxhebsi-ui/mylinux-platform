#include "dalvik/dex_header.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE* file;
    struct mylinux_dex_header header;
    size_t bytes;
    int status;

    if (argc != 2) {
        fprintf(stderr, "usage: dexinspect FILE.dex\n");
        return 2;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("dexinspect: fopen");
        return 2;
    }

    bytes = fread(&header, 1, sizeof(header), file);
    if (ferror(file)) {
        perror("dexinspect: fread");
        fclose(file);
        return 2;
    }

    if (fclose(file) != 0) {
        perror("dexinspect: fclose");
        return 2;
    }

    status = mylinux_dex_validate_header(
        &header, (uint32_t)bytes);

    printf("DEX validation: %s\n",
           mylinux_dex_status_string(status));

    if (status != MYLINUX_DEX_OK) {
        return 1;
    }

    printf("File size: %u bytes\n", header.file_size);
    printf("Header size: %u bytes\n", header.header_size);
    printf("Strings: %u\n", header.string_ids_size);
    printf("Types: %u\n", header.type_ids_size);
    printf("Methods: %u\n", header.method_ids_size);
    printf("Classes: %u\n", header.class_defs_size);
    return 0;
}
