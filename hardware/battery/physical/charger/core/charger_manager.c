#include "charger_manager.h"

int ml_charger_manager_initialize(ml_charger_device *device) {
    if (!device || !device->operations.initialize) {
        return -1;
    }

    int result = device->operations.initialize(
        device->operations.context
    );

    if (result == 0) {
        device->initialized = 1;
    }

    return result;
}

int ml_charger_manager_update(
    ml_charger_device *device,
    ml_charger_status *status
) {
    if (!device || !status || !device->initialized ||
        !device->operations.read_status) {
        return -1;
    }

    return device->operations.read_status(
        device->operations.context,
        status
    );
}
