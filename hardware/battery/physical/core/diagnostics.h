#ifndef ML_BATTERY_DIAGNOSTICS_H
#define ML_BATTERY_DIAGNOSTICS_H

#include <stdint.h>

typedef struct {
    uint32_t communication_errors;
    uint32_t invalid_measurements;
    uint32_t sensor_errors;
    uint32_t gauge_errors;
} ml_battery_diagnostics;

void ml_battery_diagnostics_reset(
    ml_battery_diagnostics *diagnostics
);

#endif
