#ifndef MYLINUX_DALVIK_DEBUGGER_H
#define MYLINUX_DALVIK_DEBUGGER_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikDebuggerAttach(DalvikVM *vm);
DalvikStatus dalvikDebuggerDetach(DalvikVM *vm);
DalvikStatus dalvikDebuggerSetBreakpoint(
    DalvikMethod *method,
    DalvikOffset offset
);
DalvikStatus dalvikDebuggerClearBreakpoint(
    DalvikMethod *method,
    DalvikOffset offset
);

#endif
