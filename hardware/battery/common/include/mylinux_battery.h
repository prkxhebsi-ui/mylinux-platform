#ifndef MYLINUX_BATTERY_H
#define MYLINUX_BATTERY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MYLINUX_BATTERY_1S = 1,
    MYLINUX_BATTERY_2S = 2,
    MYLINUX_BATTERY_3S = 3,
    MYLINUX_BATTERY_4S = 4
} mylinux_battery_configuration;

typedef struct {
    uint8_t series_cells;
    uint8_t charge_percent;
    uint8_t health_percent;

    uint32_t pack_voltage_mv;
    int32_t current_ma;
    int32_t temperature_millic;

    uint8_t is_charging;
    uint8_t is_valid;
} mylinux_battery_sample;

/*
 * Hardware-specific implementations provide this callback.
 * It reads measurements from a compatible fuel-gauge IC.
 *
 * Return 0 on success, nonzero on failure.
 */
typedef int (*mylinux_battery_read_callback)(
    void *context,
    mylinux_battery_sample *sample
);

typedef struct {
    mylinux_battery_configuration configuration;
    mylinux_battery_read_callback read_sample;
    void *context;
} mylinux_battery_device;

/* Validate the selected 1S, 2S, 3S or 4S configuration. */
int mylinux_battery_configuration_valid(
    mylinux_battery_configuration configuration
);

/* Validate a measurement received from a gauge driver. */
int mylinux_battery_sample_valid(
    const mylinux_battery_sample *sample,
    mylinux_battery_configuration configuration
);

/* Read and validate one measurement. */
int mylinux_battery_read(
    mylinux_battery_device *device,
    mylinux_battery_sample *sample
);

#ifdef __cplusplus
}
#endif

#endif
