#ifndef MYLINUX_DALVIK_VM_H
#define MYLINUX_DALVIK_VM_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikVMInitialize(DalvikVM *vm);
DalvikStatus dalvikVMExecute(DalvikVM *vm);
DalvikStatus dalvikVMStop(DalvikVM *vm);
DalvikThread *dalvikVMGetCurrentThread(DalvikVM *vm);
DalvikHeap *dalvikVMGetHeap(DalvikVM *vm);

#endif
