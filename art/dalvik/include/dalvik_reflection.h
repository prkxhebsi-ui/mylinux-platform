#ifndef MYLINUX_DALVIK_REFLECTION_H
#define MYLINUX_DALVIK_REFLECTION_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikClass *dalvikReflectGetClass(DalvikObject *object);
DalvikMethod *dalvikReflectFindMethod(
    DalvikClass *clazz,
    const char *name
);
DalvikField *dalvikReflectFindField(
    DalvikClass *clazz,
    const char *name
);

#endif
