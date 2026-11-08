/*
 * EDITABLE TEMPLATE
 * Rename and implement for your selected fuel-gauge IC.
 */

#include "mylinux_physical_battery.h"

static int custom_gauge_initialize(void *context) {
    (void)context;
    /* TODO: initialize your gauge using its datasheet. */
    return -1;
}

static int custom_gauge_read(
    void *context,
    ml_battery_measurements *sample
) {
    (void)context;
    (void)sample;

    /* TODO: read real measurements from your gauge. */
    return -1;
}

void custom_gauge_register(ml_battery_device *device) {
    if (!device) return;

    device->gauge.initialize = custom_gauge_initialize;
    device->gauge.read_measurements = custom_gauge_read;
}
