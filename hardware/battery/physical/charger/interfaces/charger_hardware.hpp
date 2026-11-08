#ifndef ML_CHARGER_HARDWARE_HPP
#define ML_CHARGER_HARDWARE_HPP

#include "charger_driver.h"

namespace mylinux {

class ChargerHardware {
public:
    virtual ~ChargerHardware() = default;

    virtual int initialize() = 0;

    virtual int readStatus(
        ml_charger_status& status
    ) = 0;

    virtual int readFaults(
        uint32_t& faults
    ) = 0;

    virtual const char *driverName() const = 0;
};

}

#endif
