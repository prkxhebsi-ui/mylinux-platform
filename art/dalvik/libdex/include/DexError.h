#ifndef MYLINUX_DEX_ERROR_H
#define MYLINUX_DEX_ERROR_H

typedef enum {
    DEX_OK = 0,
    DEX_ERROR_ARGUMENT,
    DEX_ERROR_OPEN,
    DEX_ERROR_READ,
    DEX_ERROR_MEMORY,
    DEX_ERROR_MAGIC,
    DEX_ERROR_HEADER,
    DEX_ERROR_SIZE,
    DEX_ERROR_ENDIAN,
    DEX_ERROR_TABLE,
    DEX_ERROR_INDEX,
    DEX_ERROR_STRING
} DexError;

const char *DexErrorString(DexError error);

#endif
