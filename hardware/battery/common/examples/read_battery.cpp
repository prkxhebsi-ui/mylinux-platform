#include <cstdio>
#include "mylinux_battery.hpp"

/*
 * Demonstration only.
 * Replace this callback with a real, hardware-specific
 * fuel-gauge driver before connecting physical hardware.
 */
static int example_gauge_read(
    void *context,
    mylinux_battery_sample *sample
) {
    if (!sample || !context) {
        return -1;
    }

    sample->series_cells = MYLINUX_BATTERY_1S;
    sample->charge_percent = 75;
    sample->health_percent = 98;
    sample->pack_voltage_mv = 3800;
    sample->current_ma = -250;
    sample->temperature_millic = 25000;
    sample->is_charging = 0;
    sample->is_valid = 1;

    return 0;
}

int main() {
    int hardware_placeholder = 1;

    mylinux_battery_device device = {};
    device.configuration = MYLINUX_BATTERY_1S;
    device.read_sample = example_gauge_read;
    device.context = &hardware_placeholder;

    mylinux::Battery battery(device);
    mylinux_battery_sample sample = {};

    if (battery.read(sample) != 0) {
        std::puts("Battery measurement failed.");
        return 1;
    }

    std::printf("Charge: %u%%\n", sample.charge_percent);
    std::printf("Health: %u%%\n", sample.health_percent);
    std::printf("Voltage: %u mV\n", sample.pack_voltage_mv);
    std::printf("Current: %d mA\n", sample.current_ma);
    std::printf("Temperature: %.1f C\n",
                sample.temperature_millic / 1000.0);

    return 0;
}
