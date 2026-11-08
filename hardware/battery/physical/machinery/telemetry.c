#include "mylinux_physical_battery.h"

int ml_battery_telemetry_get(
    const ml_battery_measurements *measurements,
    uint8_t *percentage,
    uint32_t *voltage_mv,
    int32_t *current_ma
) {
    if (!measurements || !percentage ||
        !voltage_mv || !current_ma) {
        return -1;
    }

    if (!measurements->measurement_valid) return -2;

    *percentage = measurements->state_of_charge;
    *voltage_mv = measurements->pack_voltage_mv;
    *current_ma = measurements->pack_current_ma;

    return 0;
}
