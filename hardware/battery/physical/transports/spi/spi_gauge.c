/*
 * SPI fuel-gauge transport backend.
 * Platform-specific SPI integration goes here.
 */
#include <stddef.h>
#include <stdint.h>

int ml_spi_gauge_transfer(
    void *bus,
    const uint8_t *transmit,
    uint8_t *receive,
    size_t length
) {
    (void)bus;
    (void)transmit;
    (void)receive;
    (void)length;
    return -1;
}
