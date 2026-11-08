#ifndef ML_TRANSPORT_INTERFACE_H
#define ML_TRANSPORT_INTERFACE_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int (*read)(void *, uint8_t, uint8_t *, size_t);
    int (*write)(void *, uint8_t, const uint8_t *, size_t);
    void *context;
} ml_battery_transport;

#endif
