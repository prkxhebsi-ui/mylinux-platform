#include "custom_pack.hpp"

int CustomBatteryPack::initialize() {
    /* TODO: connect your hardware backend. */
    return -1;
}

int CustomBatteryPack::read(
    ml_battery_measurements& measurements
) {
    (void)measurements;
    /* TODO: read actual pack measurements. */
    return -1;
}

const char *CustomBatteryPack::driverName() const {
    return "Custom Battery Pack";
}
