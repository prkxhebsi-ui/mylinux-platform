/* Pack current measurement interface implementation point. */
#include <stdint.h>

int ml_current_sensor_read_ma(
    void *device_context,
    int32_t *milliamps
) {
    (void)device_context;
    (void)milliamps;
    return -1;
}
