#include "diagnostics.h"

void ml_battery_diagnostics_reset(
    ml_battery_diagnostics *diagnostics
) {
    if (!diagnostics) return;

    diagnostics->communication_errors = 0;
    diagnostics->invalid_measurements = 0;
    diagnostics->sensor_errors = 0;
    diagnostics->gauge_errors = 0;
}
