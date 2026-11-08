#ifndef MYLINUX_DALVIK_PROPERTIES_H
#define MYLINUX_DALVIK_PROPERTIES_H

#include "dalvik_status.h"

DalvikStatus dalvikPropertySet(
    const char *name,
    const char *value
);

const char *dalvikPropertyGet(const char *name);
DalvikStatus dalvikPropertyLoadFile(const char *path);

#endif
