#ifndef MYLINUX_DALVIK_CLASS_H
#define MYLINUX_DALVIK_CLASS_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikClassLoad(
    DalvikVM *vm,
    const char *descriptor,
    DalvikClass **clazz
);

DalvikStatus dalvikClassInitialize(DalvikClass *clazz);
const char *dalvikClassGetDescriptor(DalvikClass *clazz);
DalvikMethod *dalvikClassFindMethod(DalvikClass *clazz, const char *name);
DalvikField *dalvikClassFindField(DalvikClass *clazz, const char *name);

#endif
