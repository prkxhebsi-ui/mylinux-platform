#ifndef MYLINUX_DALVIK_INSTRUCTION_H
#define MYLINUX_DALVIK_INSTRUCTION_H

#include "dalvik_types.h"

typedef struct {
    DalvikU1 opcode;
    DalvikU1 width;
    DalvikU2 flags;
} DalvikInstructionInfo;

DalvikU1 dalvikInstructionGetOpcode(const DalvikU2 *code);
DalvikU4 dalvikInstructionGetWidth(const DalvikU2 *code);
const DalvikInstructionInfo *dalvikInstructionGetInfo(DalvikU1 opcode);

#endif
