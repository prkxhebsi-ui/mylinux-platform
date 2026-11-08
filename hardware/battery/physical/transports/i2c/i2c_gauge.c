/*
 * I2C fuel-gauge transport backend.
 * Connect to the platform I2C subsystem here.
 */
#include <stddef.h>
#include <stdint.h>

int ml_i2c_gauge_read(
    void *bus,
    uint8_t address,
    uint8_t *data,
    size_t length
) {
    (void)bus;
    (void)address;
    (void)data;
    (void)length;
    return -1;
}
