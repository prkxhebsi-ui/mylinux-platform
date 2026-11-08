#ifndef ML_CANONICAL_GAUGE_REFERENCE_CPP
#define ML_CANONICAL_GAUGE_REFERENCE_CPP

#include "battery_hardware.hpp"

/*
 * Canonical C++ interface reference.
 * Copy this file before creating a hardware driver.
 */

namespace mylinux {

class CanonicalGaugeReference : public BatteryHardware {
public:
    int initialize() override;
    int read(ml_battery_measurements& measurements) override;
    const char *driverName() const override;
};

}

#endif
