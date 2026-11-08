#ifndef MYLINUX_DALVIK_NATIVE_H
#define MYLINUX_DALVIK_NATIVE_H

#include "dalvik_types.h"
#include "dalvik_status.h"

typedef void (*DalvikNativeFunction)(void);

DalvikStatus dalvikNativeRegister(
    DalvikVM *vm,
    const char *class_name,
    const char *method_name,
    DalvikNativeFunction function
);

DalvikStatus dalvikNativeUnregister(
    DalvikVM *vm,
    const char *class_name,
    const char *method_name
);

#endif
