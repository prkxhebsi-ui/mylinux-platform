#ifndef MYLINUX_DALVIK_THREAD_H
#define MYLINUX_DALVIK_THREAD_H

#include "dalvik_types.h"
#include "dalvik_status.h"

DalvikStatus dalvikThreadCreate(DalvikVM *vm, DalvikThread **thread);
DalvikStatus dalvikThreadStart(DalvikThread *thread);
DalvikStatus dalvikThreadSuspend(DalvikThread *thread);
DalvikStatus dalvikThreadResume(DalvikThread *thread);
DalvikStatus dalvikThreadTerminate(DalvikThread *thread);
DalvikThread *dalvikThreadCurrent(void);

#endif
