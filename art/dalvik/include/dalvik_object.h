#ifndef MYLINUX_DALVIK_OBJECT_H
#define MYLINUX_DALVIK_OBJECT_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikObjectAllocate(
    DalvikVM *vm,
    DalvikClass *clazz,
    DalvikObject **object
);

DalvikClass *dalvikObjectGetClass(DalvikObject *object);
DalvikStatus dalvikObjectRelease(DalvikVM *vm, DalvikObject *object);

#endif
