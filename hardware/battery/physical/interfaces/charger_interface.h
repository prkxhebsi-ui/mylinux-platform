#ifndef ML_CHARGER_INTERFACE_H
#define ML_CHARGER_INTERFACE_H

typedef struct {
    int (*read_status)(void *context, int *charging);
    void *context;
} ml_charger_status_driver;

/* Status reporting only; no charger control is defined here. */

#endif
