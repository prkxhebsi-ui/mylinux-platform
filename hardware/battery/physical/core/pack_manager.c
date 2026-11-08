#include "pack_manager.h"

int ml_pack_manager_initialize(ml_battery_device *device) {
    return ml_battery_initialize(device);
}

int ml_pack_manager_update(
    ml_battery_device *device,
    ml_battery_measurements *measurements
) {
    return ml_battery_read(device, measurements);
}
