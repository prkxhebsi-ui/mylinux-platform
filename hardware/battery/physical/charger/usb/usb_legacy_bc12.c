#include "usb_common.h"

/*
 * Legacy USB charging-port detection interface.
 *
 * SDP: Standard Downstream Port
 * CDP: Charging Downstream Port
 * DCP: Dedicated Charging Port
 *
 * Actual detection is performed by a compatible PHY,
 * charger IC or USB charging-port detection controller.
 */

int ml_usb_legacy_read_detection(
    void *controller,
    ml_usb_power_information *information
) {
    (void)controller;
    (void)information;

    /* Hardware-specific implementation required. */
    return -1;
}
