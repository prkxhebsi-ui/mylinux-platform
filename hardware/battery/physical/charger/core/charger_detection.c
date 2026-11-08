#include "../interfaces/charger_driver.h"

ml_charger_type ml_charger_detect_type(
    const ml_charger_status *status
) {
    if (!status || !status->valid) {
        return ML_CHARGER_NONE;
    }

    return status->type;
}
