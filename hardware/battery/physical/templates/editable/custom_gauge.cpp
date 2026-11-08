/* EDITABLE C++ fuel-gauge template. */

#include "battery_hardware.hpp"

class CustomGauge : public mylinux::BatteryHardware {
public:
    int initialize() override {
        /* TODO: initialize your selected gauge. */
        return -1;
    }

    int read(
        ml_battery_measurements& measurements
    ) override {
        (void)measurements;
        /* TODO: obtain actual gauge readings. */
        return -1;
    }

    const char *driverName() const override {
        return "Custom MyLinux Gauge";
    }
};
