#ifndef ML_SENSOR_INTERFACE_H
#define ML_SENSOR_INTERFACE_H

#include <stdint.h>

typedef struct {
    int (*read_voltage_mv)(void *, uint32_t *);
    int (*read_current_ma)(void *, int32_t *);
    int (*read_temperature_mc)(void *, int32_t *);
    void *context;
} ml_battery_sensor_driver;

#endif
