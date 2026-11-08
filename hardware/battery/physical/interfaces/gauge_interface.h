#ifndef ML_GAUGE_INTERFACE_H
#define ML_GAUGE_INTERFACE_H

#include "mylinux_physical_battery.h"

typedef struct {
    const char *name;
    int (*probe)(void *context);
    int (*read)(void *context, ml_battery_measurements *sample);
    void *context;
} ml_gauge_driver;

#endif
