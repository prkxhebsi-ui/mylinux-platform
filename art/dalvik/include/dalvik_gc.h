#ifndef MYLINUX_DALVIK_GC_H
#define MYLINUX_DALVIK_GC_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikGCInitialize(DalvikVM *vm);
DalvikStatus dalvikGCCollect(DalvikVM *vm);
void dalvikGCEnable(DalvikVM *vm);
void dalvikGCDisable(DalvikVM *vm);
size_t dalvikGCGetLiveBytes(DalvikVM *vm);

#endif
