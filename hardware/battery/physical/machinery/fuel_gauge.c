/*
 * Fuel-gauge discovery and integration point.
 * Implementations should use the selected IC datasheet.
 */
#include <stdint.h>

int ml_fuel_gauge_detect(void *transport_context) {
    (void)transport_context;
    return -1;
}
