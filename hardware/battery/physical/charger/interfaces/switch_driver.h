#ifndef ML_SWITCH_DRIVER_H
#define ML_SWITCH_DRIVER_H

#include <stdint.h>

typedef struct {
    uint8_t state_known;
    uint8_t conducting;
    uint8_t fault;
} ml_power_switch_status;

typedef struct {
    int (*read_status)(
        void *context,
        ml_power_switch_status *status
    );
    void *context;
} ml_power_switch_operations;

#endif
