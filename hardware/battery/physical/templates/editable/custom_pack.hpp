#ifndef ML_CUSTOM_PACK_TEMPLATE_HPP
#define ML_CUSTOM_PACK_TEMPLATE_HPP

#include "battery_hardware.hpp"

class CustomBatteryPack : public mylinux::BatteryHardware {
public:
    int initialize() override;
    int read(ml_battery_measurements& measurements) override;
    const char *driverName() const override;
};

#endif
