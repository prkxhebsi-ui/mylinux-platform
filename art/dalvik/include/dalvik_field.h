#ifndef MYLINUX_DALVIK_FIELD_H
#define MYLINUX_DALVIK_FIELD_H

#include "dalvik_types.h"
#include "dalvik_status.h"

const char *dalvikFieldGetName(DalvikField *field);
DalvikStatus dalvikFieldGetValue(
    DalvikObject *object,
    DalvikField *field,
    void *value
);
DalvikStatus dalvikFieldSetValue(
    DalvikObject *object,
    DalvikField *field,
    const void *value
);

#endif
