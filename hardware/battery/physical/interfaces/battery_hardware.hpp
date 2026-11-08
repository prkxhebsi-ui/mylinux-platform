#ifndef ML_BATTERY_HARDWARE_HPP
#define ML_BATTERY_HARDWARE_HPP

#include "mylinux_physical_battery.h"

namespace mylinux {

class BatteryHardware {
public:
    virtual ~BatteryHardware() = default;

    virtual int initialize() = 0;

    virtual int read(
        ml_battery_measurements& measurements
    ) = 0;

    virtual const char *driverName() const = 0;
};

} // namespace mylinux

#endif
