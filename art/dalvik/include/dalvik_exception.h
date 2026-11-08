#ifndef MYLINUX_DALVIK_EXCEPTION_H
#define MYLINUX_DALVIK_EXCEPTION_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikExceptionThrow(
    DalvikThread *thread,
    DalvikException *exception
);

DalvikException *dalvikExceptionGetPending(DalvikThread *thread);
void dalvikExceptionClear(DalvikThread *thread);
bool dalvikExceptionIsPending(DalvikThread *thread);

#endif
