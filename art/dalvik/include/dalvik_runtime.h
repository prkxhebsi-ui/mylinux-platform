#ifndef MYLINUX_DALVIK_RUNTIME_H
#define MYLINUX_DALVIK_RUNTIME_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikRuntimeCreate(DalvikVM **vm);
DalvikStatus dalvikRuntimeStart(DalvikVM *vm);
DalvikStatus dalvikRuntimeShutdown(DalvikVM *vm);
void dalvikRuntimeDestroy(DalvikVM *vm);

#endif
