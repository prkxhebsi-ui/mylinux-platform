#ifndef MYLINUX_DALVIK_VERIFIER_H
#define MYLINUX_DALVIK_VERIFIER_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikVerifyDexFile(DalvikDexFile *dex);
DalvikStatus dalvikVerifyClass(DalvikClass *clazz);
DalvikStatus dalvikVerifyMethod(DalvikMethod *method);

#endif
