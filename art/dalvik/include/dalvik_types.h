#ifndef MYLINUX_DALVIK_TYPES_H
#define MYLINUX_DALVIK_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint8_t  DalvikU1;
typedef uint16_t DalvikU2;
typedef uint32_t DalvikU4;
typedef uint64_t DalvikU8;

typedef int8_t  DalvikS1;
typedef int16_t DalvikS2;
typedef int32_t DalvikS4;
typedef int64_t DalvikS8;

typedef uint32_t DalvikReg;
typedef uint32_t DalvikIndex;
typedef uint32_t DalvikOffset;
typedef uint32_t DalvikMethodIndex;
typedef uint32_t DalvikFieldIndex;
typedef uint32_t DalvikTypeIndex;

typedef struct DalvikVM DalvikVM;
typedef struct DalvikThread DalvikThread;
typedef struct DalvikObject DalvikObject;
typedef struct DalvikClass DalvikClass;
typedef struct DalvikMethod DalvikMethod;
typedef struct DalvikField DalvikField;
typedef struct DalvikHeap DalvikHeap;
typedef struct DalvikDexFile DalvikDexFile;
typedef struct DalvikException DalvikException;
typedef struct DalvikFrame DalvikFrame;

typedef uintptr_t DalvikHandle;

#endif
