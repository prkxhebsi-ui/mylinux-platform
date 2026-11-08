#include "charge_estimator.h"

int ml_charge_estimator_validate(
    const ml_battery_measurements *m
) {
    if (!m) return 0;
    if (m->state_of_charge > 100) return 0;
    if (m->state_of_health > 100) return 0;
    if (!m->measurement_valid) return 0;
    return 1;
}

uint8_t ml_charge_estimator_percentage(
    const ml_battery_measurements *m
) {
    if (!ml_charge_estimator_validate(m)) return 0;
    return m->state_of_charge;
}
