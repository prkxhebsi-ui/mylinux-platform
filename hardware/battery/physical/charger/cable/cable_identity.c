#include <stdint.h>

/*
 * Cable identity is supplied by the Type-C/PD controller.
 * Some USB-C cables have an electronic marker (e-marker).
 * Passive cables do not contain executable software.
 */

typedef struct {
    uint32_t vendor_id;
    uint32_t product_id;
    uint32_t maximum_current_ma;
    uint32_t maximum_voltage_mv;
    uint8_t electronic_marker_present;
    uint8_t identity_valid;
} ml_cable_identity;

int ml_cable_read_identity(
    void *pd_controller,
    ml_cable_identity *identity
) {
    (void)pd_controller;
    (void)identity;
    return -1;
}
