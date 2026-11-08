#include "battery_events.h"

static ml_battery_event_callback event_callback = 0;

void ml_battery_set_event_callback(
    ml_battery_event_callback callback
) {
    event_callback = callback;
}

void ml_battery_emit_event(ml_battery_event event) {
    if (event_callback) {
        event_callback(event);
    }
}
