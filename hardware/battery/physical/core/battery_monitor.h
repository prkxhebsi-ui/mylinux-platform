#ifndef ML_BATTERY_MONITOR_H
#define ML_BATTERY_MONITOR_H

#include "mylinux_physical_battery.h"

typedef struct {
    ml_battery_measurements latest;
    uint32_t successful_reads;
    uint32_t failed_reads;
} ml_battery_monitor;

void ml_battery_monitor_reset(ml_battery_monitor *monitor);

int ml_battery_monitor_update(
    ml_battery_monitor *monitor,
    ml_battery_device *device
);

#endif
