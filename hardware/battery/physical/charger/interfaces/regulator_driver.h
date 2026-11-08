#ifndef ML_REGULATOR_DRIVER_H
#define ML_REGULATOR_DRIVER_H

#include <stdint.h>

typedef struct {
    uint32_t output_voltage_mv;
    uint32_t output_current_ma;
    uint8_t enabled;
    uint8_t fault;
    uint8_t valid;
} ml_regulator_status;

typedef struct {
    int (*read_status)(
        void *context,
        ml_regulator_status *status
    );
    void *context;
} ml_regulator_operations;

#endif
