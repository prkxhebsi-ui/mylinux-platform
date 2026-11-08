#include <trusty/trusty.h>

int trusty_initialize(trusty_system_t *system)
{
    if (!system)
        return -1;

    system->state = TRUSTY_STATE_INITIALIZING;
    system->version = 1;
    system->app_count = 0;

    system->state = TRUSTY_STATE_READY;
    return 0;
}

const char *trusty_state_name(trusty_state_t state)
{
    switch (state) {
    case TRUSTY_STATE_OFFLINE:
        return "OFFLINE";
    case TRUSTY_STATE_INITIALIZING:
        return "INITIALIZING";
    case TRUSTY_STATE_READY:
        return "READY";
    case TRUSTY_STATE_ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
