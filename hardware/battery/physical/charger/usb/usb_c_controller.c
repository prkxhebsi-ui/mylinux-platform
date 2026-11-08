#include "usb_common.h"

/*
 * USB Type-C controller status interface.
 * Connector orientation, attachment and CC status
 * must be obtained from a compliant Type-C controller.
 */

int ml_usb_c_read_status(
    void *controller,
    ml_usb_power_information *information
) {
    (void)controller;
    (void)information;
    return -1;
}
