#ifndef MYLINUX_DALVIK_JDWP_H
#define MYLINUX_DALVIK_JDWP_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikJdwpInitialize(DalvikVM *vm);
DalvikStatus dalvikJdwpStart(DalvikVM *vm);
DalvikStatus dalvikJdwpStop(DalvikVM *vm);
DalvikStatus dalvikJdwpProcessPacket(DalvikVM *vm);

#endif
