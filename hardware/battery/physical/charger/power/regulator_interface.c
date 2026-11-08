#include "../interfaces/regulator_driver.h"

int ml_regulator_read_status(
    ml_regulator_operations *operations,
    ml_regulator_status *status
) {
    if (!operations || !status || !operations->read_status) {
        return -1;
    }

    return operations->read_status(
        operations->context,
        status
    );
}
