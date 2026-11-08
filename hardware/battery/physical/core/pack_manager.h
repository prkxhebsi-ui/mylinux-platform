#ifndef ML_PACK_MANAGER_H
#define ML_PACK_MANAGER_H

#include "mylinux_physical_battery.h"

int ml_pack_manager_initialize(ml_battery_device *device);
int ml_pack_manager_update(
    ml_battery_device *device,
    ml_battery_measurements *measurements
);

#endif
