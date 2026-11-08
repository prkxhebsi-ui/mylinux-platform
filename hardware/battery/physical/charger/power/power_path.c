#include <stdint.h>

typedef struct {
    uint8_t input_present;
    uint8_t battery_connected;
    uint8_t system_powered;
    uint8_t fault;
} ml_power_path_status;

/*
 * Read-only power-path status integration point.
 */
int ml_power_path_read(
    void *power_controller,
    ml_power_path_status *status
) {
    (void)power_controller;
    (void)status;
    return -1;
}
