#ifndef MYLINUX_DALVIK_METHOD_H
#define MYLINUX_DALVIK_METHOD_H

#include "dalvik_types.h"
#include "dalvik_status.h"

const char *dalvikMethodGetName(DalvikMethod *method);
DalvikClass *dalvikMethodGetDeclaringClass(DalvikMethod *method);
DalvikStatus dalvikMethodInvoke(
    DalvikThread *thread,
    DalvikMethod *method,
    DalvikObject *receiver
);

#endif
