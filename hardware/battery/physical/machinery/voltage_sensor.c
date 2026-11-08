/*
 * MyLinux voltage measurement machinery.
 * Hardware-specific ADC or gauge implementation belongs here.
 */
#include <stdint.h>

int ml_voltage_sensor_read_mv(
    void *device_context,
    uint32_t *millivolts
) {
    (void)device_context;
    (void)millivolts;

    /* Not implemented until a hardware backend is supplied. */
    return -1;
}
