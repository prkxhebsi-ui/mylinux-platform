/*
 * EDITABLE TEMPLATE
 * Implement for a selected charger IC.
 */

#include "../../interfaces/charger_driver.h"

static int custom_initialize(void *context) {
    (void)context;
    /* TODO: initialize the selected charger IC. */
    return -1;
}

static int custom_read_status(
    void *context,
    ml_charger_status *status
) {
    (void)context;
    (void)status;
    /* TODO: read real hardware status. */
    return -1;
}

static int custom_read_faults(
    void *context,
    uint32_t *faults
) {
    (void)context;
    (void)faults;
    /* TODO: read hardware fault registers. */
    return -1;
}

void custom_charger_register(ml_charger_device *device) {
    if (!device) return;

    device->operations.initialize = custom_initialize;
    device->operations.read_status = custom_read_status;
    device->operations.read_faults = custom_read_faults;
}
