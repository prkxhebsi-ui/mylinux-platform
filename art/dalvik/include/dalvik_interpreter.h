#ifndef MYLINUX_DALVIK_INTERPRETER_H
#define MYLINUX_DALVIK_INTERPRETER_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikInterpreterInitialize(DalvikVM *vm);
DalvikStatus dalvikInterpreterExecute(
    DalvikThread *thread,
    DalvikMethod *method
);
DalvikStatus dalvikInterpreterStep(DalvikThread *thread);

#endif
