#ifndef ML_CANONICAL_GAUGE_REFERENCE_H
#define ML_CANONICAL_GAUGE_REFERENCE_H

#include "mylinux_physical_battery.h"

/*
 * Canonical interface reference.
 * Do not implement hardware behavior in this file.
 */
typedef struct {
    int (*probe)(void *context);
    int (*initialize)(void *context);
    int (*read_sample)(
        void *context,
        ml_battery_measurements *sample
    );
    void *context;
} ml_canonical_gauge_reference;

#endif
