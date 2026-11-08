#ifndef ML_CHARGER_MANAGER_H
#define ML_CHARGER_MANAGER_H

#include "../interfaces/charger_driver.h"

int ml_charger_manager_initialize(ml_charger_device *device);

int ml_charger_manager_update(
    ml_charger_device *device,
    ml_charger_status *status
);

#endif
