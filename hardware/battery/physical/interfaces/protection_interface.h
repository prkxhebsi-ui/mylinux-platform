#ifndef ML_PROTECTION_INTERFACE_H
#define ML_PROTECTION_INTERFACE_H

typedef struct {
    int (*read_fault_status)(void *context, unsigned int *faults);
    void *context;
} ml_protection_status_driver;

/* Reports independent protection hardware status only. */

#endif
