#ifndef MYLINUX_TRUSTY_H
#define MYLINUX_TRUSTY_H

#include <stdint.h>

typedef enum {
    TRUSTY_STATE_OFFLINE = 0,
    TRUSTY_STATE_INITIALIZING,
    TRUSTY_STATE_READY,
    TRUSTY_STATE_ERROR
} trusty_state_t;

typedef struct {
    trusty_state_t state;
    uint32_t version;
    uint32_t app_count;
} trusty_system_t;

int trusty_initialize(trusty_system_t *system);
const char *trusty_state_name(trusty_state_t state);

#endif
