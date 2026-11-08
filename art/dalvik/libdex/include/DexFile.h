#ifndef MYLINUX_DEX_FILE_H
#define MYLINUX_DEX_FILE_H

#include <stdint.h>
#include <stddef.h>

#include "DexFormat.h"
#include "DexError.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DexFile DexFile;

DexError DexFileOpen(const char *path, DexFile **result);

DexError DexFileOpenMemory(
    const void *data,
    size_t size,
    DexFile **result
);

void DexFileClose(DexFile *dex);

const DexHeader *DexFileGetHeader(const DexFile *dex);

const uint8_t *DexFileGetData(const DexFile *dex);

size_t DexFileGetSize(const DexFile *dex);

DexError DexFileGetString(
    const DexFile *dex,
    uint32_t index,
    DexStringData *result
);

DexError DexFileValidate(const DexFile *dex);

#ifdef __cplusplus
}
#endif

#endif
