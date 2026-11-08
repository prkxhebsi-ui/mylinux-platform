#include "battery_monitor.h"

void ml_battery_monitor_reset(ml_battery_monitor *monitor) {
    if (!monitor) return;

    monitor->successful_reads = 0;
    monitor->failed_reads = 0;
    monitor->latest.measurement_valid = 0;
}

int ml_battery_monitor_update(
    ml_battery_monitor *monitor,
    ml_battery_device *device
) {
    if (!monitor || !device) return -1;

    int result = ml_battery_read(device, &monitor->latest);

    if (result == 0) {
        monitor->successful_reads++;
    } else {
        monitor->failed_reads++;
    }

    return result;
}
