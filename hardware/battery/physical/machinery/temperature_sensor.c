/* Battery temperature sensor implementation point. */
#include <stdint.h>

int ml_temperature_sensor_read_mc(
    void *device_context,
    int32_t *temperature_mc
) {
    (void)device_context;
    (void)temperature_mc;
    return -1;
}
