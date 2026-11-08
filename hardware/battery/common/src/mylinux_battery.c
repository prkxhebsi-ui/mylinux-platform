#include "mylinux_battery.h"

int mylinux_battery_configuration_valid(
    mylinux_battery_configuration configuration
) {
    return configuration >= MYLINUX_BATTERY_1S &&
           configuration <= MYLINUX_BATTERY_4S;
}

int mylinux_battery_sample_valid(
    const mylinux_battery_sample *sample,
    mylinux_battery_configuration configuration
) {
    if (sample == 0) {
        return 0;
    }

    if (!mylinux_battery_configuration_valid(configuration)) {
        return 0;
    }

    if (sample->series_cells != (uint8_t)configuration) {
        return 0;
    }

    if (sample->charge_percent > 100 ||
        sample->health_percent > 100) {
        return 0;
    }

    if (sample->pack_voltage_mv == 0) {
        return 0;
    }

    if (sample->temperature_millic < -40000 ||
        sample->temperature_millic > 125000) {
        return 0;
    }

    if (sample->is_charging > 1 || sample->is_valid > 1) {
        return 0;
    }

    return sample->is_valid != 0;
}

int mylinux_battery_read(
    mylinux_battery_device *device,
    mylinux_battery_sample *sample
) {
    if (device == 0 || sample == 0 ||
        device->read_sample == 0) {
        return -1;
    }

    if (!mylinux_battery_configuration_valid(
            device->configuration)) {
        return -2;
    }

    if (device->read_sample(device->context, sample) != 0) {
        return -3;
    }

    if (!mylinux_battery_sample_valid(
            sample, device->configuration)) {
        return -4;
    }

    return 0;
}
