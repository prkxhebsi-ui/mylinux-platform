#ifndef MYLINUX_DALVIK_DEX_H
#define MYLINUX_DALVIK_DEX_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikDexOpen(
    const char *path,
    DalvikDexFile **dex
);

DalvikStatus dalvikDexOpenMemory(
    const void *data,
    size_t size,
    DalvikDexFile **dex
);

void dalvikDexClose(DalvikDexFile *dex);
DalvikStatus dalvikDexValidate(DalvikDexFile *dex);
uint32_t dalvikDexGetVersion(DalvikDexFile *dex);

#endif
