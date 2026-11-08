#include "../interfaces/switch_driver.h"

/*
 * Reports the state of a hardware power-path switch.
 *
 * MOSFETs and other transistors must be controlled by
 * a suitable power-management controller and its
 * documented safety circuitry.
 */

int ml_transistor_switch_read_status(
    ml_power_switch_operations *operations,
    ml_power_switch_status *status
) {
    if (!operations || !status || !operations->read_status) {
        return -1;
    }

    return operations->read_status(
        operations->context,
        status
    );
}
