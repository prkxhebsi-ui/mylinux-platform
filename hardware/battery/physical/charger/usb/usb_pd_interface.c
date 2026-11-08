#include <stdint.h>

typedef struct {
    uint32_t voltage_mv;
    uint32_t current_ma;
    uint32_t power_mw;
    uint8_t contract_valid;
} ml_usb_pd_contract;

/*
 * Read-only USB Power Delivery contract interface.
 * A compliant PD controller performs negotiation.
 * This module does not construct arbitrary PD messages.
 */

int ml_usb_pd_read_contract(
    void *controller,
    ml_usb_pd_contract *contract
) {
    (void)controller;
    (void)contract;
    return -1;
}
