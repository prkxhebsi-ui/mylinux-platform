/* EDITABLE regulator status driver template. */

#include "../../interfaces/regulator_driver.h"

int custom_regulator_read(
    void *context,
    ml_regulator_status *status
) {
    (void)context;
    (void)status;
    /* TODO: read regulator status from hardware. */
    return -1;
}
