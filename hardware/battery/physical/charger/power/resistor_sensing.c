#include <stdint.h>

/*
 * Measurement interface for a current-sense resistor.
 *
 * Actual current measurement requires a suitable
 * current-sense amplifier or fuel-gauge IC.
 */

int ml_resistor_sense_read(
    void *sense_amplifier,
    int32_t *current_ma
) {
    (void)sense_amplifier;
    (void)current_ma;
    return -1;
}
