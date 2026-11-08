#ifndef ML_CHARGE_ESTIMATOR_H
#define ML_CHARGE_ESTIMATOR_H

#include "mylinux_physical_battery.h"

int ml_charge_estimator_validate(
    const ml_battery_measurements *measurements
);

uint8_t ml_charge_estimator_percentage(
    const ml_battery_measurements *measurements
);

#endif
