/* EDITABLE power-switch status driver template. */

#include "../../interfaces/switch_driver.h"

int custom_switch_read(
    void *context,
    ml_power_switch_status *status
) {
    (void)context;
    (void)status;
    /* TODO: report the hardware controller's switch state. */
    return -1;
}
