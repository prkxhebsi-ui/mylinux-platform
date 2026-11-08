#ifndef ML_BATTERY_EVENTS_H
#define ML_BATTERY_EVENTS_H

typedef enum {
    ML_EVENT_GAUGE_CONNECTED,
    ML_EVENT_GAUGE_DISCONNECTED,
    ML_EVENT_MEASUREMENT_UPDATED,
    ML_EVENT_MEASUREMENT_FAILED,
    ML_EVENT_BATTERY_IDENTIFIED,
    ML_EVENT_BATTERY_REMOVED
} ml_battery_event;

typedef void (*ml_battery_event_callback)(ml_battery_event event);

void ml_battery_set_event_callback(
    ml_battery_event_callback callback
);

void ml_battery_emit_event(ml_battery_event event);

#endif
