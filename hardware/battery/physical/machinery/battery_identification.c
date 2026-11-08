#include "mylinux_physical_battery.h"

int ml_battery_identification_read(
    ml_battery_gauge_operations *operations,
    ml_battery_identity *identity
) {
    if (!operations || !identity ||
        !operations->read_identity) {
        return -1;
    }

    return operations->read_identity(
        operations->context,
        identity
    );
}
