#include "DexFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DexFile {
    uint8_t *data;
    size_t size;
    DexHeader header;
};

static uint32_t readU32(const uint8_t *p) {
    return ((uint32_t)p[0]) |
           ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static void parseHeader(DexHeader *h, const uint8_t *p) {
    memcpy(h->magic, p, 8);
    h->checksum = readU32(p + 8);
    memcpy(h->signature, p + 12, 20);

    h->file_size = readU32(p + 32);
    h->header_size = readU32(p + 36);
    h->endian_tag = readU32(p + 40);

    h->link_size = readU32(p + 44);
    h->link_off = readU32(p + 48);
    h->map_off = readU32(p + 52);

    h->string_ids_size = readU32(p + 56);
    h->string_ids_off = readU32(p + 60);

    h->type_ids_size = readU32(p + 64);
    h->type_ids_off = readU32(p + 68);

    h->proto_ids_size = readU32(p + 72);
    h->proto_ids_off = readU32(p + 76);

    h->field_ids_size = readU32(p + 80);
    h->field_ids_off = readU32(p + 84);

    h->method_ids_size = readU32(p + 88);
    h->method_ids_off = readU32(p + 92);

    h->class_defs_size = readU32(p + 96);
    h->class_defs_off = readU32(p + 100);

    h->data_size = readU32(p + 104);
    h->data_off = readU32(p + 108);
}

static int validMagic(const uint8_t *magic) {
    if (memcmp(magic, "dex\n", 4) != 0)
        return 0;

    if (magic[4] < '0' || magic[4] > '9' ||
        magic[5] < '0' || magic[5] > '9' ||
        magic[6] < '0' || magic[6] > '9')
        return 0;

    return magic[7] == '\0';
}

static int tableInBounds(
    uint32_t offset,
    uint32_t count,
    uint32_t item_size,
    size_t file_size
) {
    if (count == 0)
        return offset == 0 || offset <= file_size;

    if (offset == 0)
        return 0;

    uint64_t end =
        (uint64_t)offset +
        (uint64_t)count * item_size;

    return end <= file_size;
}

static DexError validateHeader(DexFile *dex) {
    DexHeader *h = &dex->header;

    if (!validMagic(h->magic))
        return DEX_ERROR_MAGIC;

    if (h->header_size != DEX_HEADER_SIZE ||
        h->header_size > dex->size)
        return DEX_ERROR_HEADER;

    if (h->file_size != dex->size ||
        h->file_size < DEX_HEADER_SIZE)
        return DEX_ERROR_SIZE;

    if (h->endian_tag != DEX_ENDIAN_CONSTANT)
        return DEX_ERROR_ENDIAN;

    if (!tableInBounds(h->string_ids_off,
                       h->string_ids_size,
                       DEX_STRING_ID_SIZE, dex->size))
        return DEX_ERROR_TABLE;

    if (!tableInBounds(h->type_ids_off,
                       h->type_ids_size,
                       DEX_TYPE_ID_SIZE, dex->size))
        return DEX_ERROR_TABLE;

    if (!tableInBounds(h->proto_ids_off,
                       h->proto_ids_size,
                       DEX_PROTO_ID_SIZE, dex->size))
        return DEX_ERROR_TABLE;

    if (!tableInBounds(h->field_ids_off,
                       h->field_ids_size,
                       DEX_FIELD_ID_SIZE, dex->size))
        return DEX_ERROR_TABLE;

    if (!tableInBounds(h->method_ids_off,
                       h->method_ids_size,
                       DEX_METHOD_ID_SIZE, dex->size))
        return DEX_ERROR_TABLE;

    if (!tableInBounds(h->class_defs_off,
                       h->class_defs_size,
                       DEX_CLASS_DEF_SIZE, dex->size))
        return DEX_ERROR_TABLE;

    if (h->data_size > 0) {
        if (h->data_off < DEX_HEADER_SIZE ||
            (uint64_t)h->data_off + h->data_size > dex->size)
            return DEX_ERROR_TABLE;
    } else if (h->data_off != 0) {
        return DEX_ERROR_TABLE;
    }

    if (h->link_size > 0) {
        if (h->link_off == 0 ||
            (uint64_t)h->link_off + h->link_size > dex->size)
            return DEX_ERROR_TABLE;
    }

    if (h->map_off != 0 &&
        h->map_off > dex->size - 4)
        return DEX_ERROR_TABLE;

    return DEX_OK;
}

DexError DexFileOpenMemory(
    const void *input,
    size_t size,
    DexFile **result
) {
    if (!input || !result)
        return DEX_ERROR_ARGUMENT;

    *result = NULL;

    if (size < DEX_HEADER_SIZE)
        return DEX_ERROR_SIZE;

    DexFile *dex = calloc(1, sizeof(*dex));
    if (!dex)
        return DEX_ERROR_MEMORY;

    dex->data = malloc(size);
    if (!dex->data) {
        free(dex);
        return DEX_ERROR_MEMORY;
    }

    memcpy(dex->data, input, size);
    dex->size = size;

    parseHeader(&dex->header, dex->data);

    DexError error = validateHeader(dex);
    if (error != DEX_OK) {
        DexFileClose(dex);
        return error;
    }

    *result = dex;
    return DEX_OK;
}

DexError DexFileOpen(const char *path, DexFile **result) {
    if (!path || !result)
        return DEX_ERROR_ARGUMENT;

    *result = NULL;

    FILE *file = fopen(path, "rb");
    if (!file)
        return DEX_ERROR_OPEN;

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return DEX_ERROR_READ;
    }

    long length = ftell(file);
    if (length < DEX_HEADER_SIZE) {
        fclose(file);
        return DEX_ERROR_SIZE;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return DEX_ERROR_READ;
    }

    size_t size = (size_t)length;
    uint8_t *buffer = malloc(size);

    if (!buffer) {
        fclose(file);
        return DEX_ERROR_MEMORY;
    }

    size_t read_count = fread(buffer, 1, size, file);
    fclose(file);

    if (read_count != size) {
        free(buffer);
        return DEX_ERROR_READ;
    }

    DexError error = DexFileOpenMemory(buffer, size, result);
    free(buffer);

    return error;
}

void DexFileClose(DexFile *dex) {
    if (!dex)
        return;

    free(dex->data);
    free(dex);
}

const DexHeader *DexFileGetHeader(const DexFile *dex) {
    return dex ? &dex->header : NULL;
}

const uint8_t *DexFileGetData(const DexFile *dex) {
    return dex ? dex->data : NULL;
}

size_t DexFileGetSize(const DexFile *dex) {
    return dex ? dex->size : 0;
}

DexError DexFileValidate(const DexFile *dex) {
    if (!dex)
        return DEX_ERROR_ARGUMENT;

    return validateHeader((DexFile *)dex);
}

static int readUleb128(
    const uint8_t *data,
    size_t size,
    size_t *position,
    uint32_t *value
) {
    uint32_t result = 0;
    unsigned int shift = 0;

    for (unsigned int i = 0; i < 5; i++) {
        if (*position >= size)
            return 0;

        uint8_t byte = data[(*position)++];

        if (i == 4 && (byte & 0xF0))
            return 0;

        result |= ((uint32_t)(byte & 0x7F)) << shift;

        if (!(byte & 0x80)) {
            *value = result;
            return 1;
        }

        shift += 7;
    }

    return 0;
}

DexError DexFileGetString(
    const DexFile *dex,
    uint32_t index,
    DexStringData *result
) {
    if (!dex || !result)
        return DEX_ERROR_ARGUMENT;

    if (index >= dex->header.string_ids_size)
        return DEX_ERROR_INDEX;

    uint32_t string_offset = readU32(
        dex->data + dex->header.string_ids_off + index * 4
    );

    if (string_offset >= dex->size)
        return DEX_ERROR_STRING;

    size_t position = string_offset;
    uint32_t utf16_size = 0;

    if (!readUleb128(
        dex->data,
        dex->size,
        &position,
        &utf16_size
    ))
        return DEX_ERROR_STRING;

    size_t start = position;

    while (position < dex->size && dex->data[position] != 0)
        position++;

    if (position >= dex->size)
        return DEX_ERROR_STRING;

    result->utf16_size = utf16_size;
    result->data = (const char *)(dex->data + start);
    result->byte_length = position - start;

    return DEX_OK;
}
