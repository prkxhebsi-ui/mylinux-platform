#include <stdint.h>

typedef enum {
    ML_CHARGER_EVENT_CONNECTED,
    ML_CHARGER_EVENT_DISCONNECTED,
    ML_CHARGER_EVENT_TYPE_CHANGED,
    ML_CHARGER_EVENT_CHARGING,
    ML_CHARGER_EVENT_COMPLETE,
    ML_CHARGER_EVENT_FAULT
} ml_charger_event;

typedef void (*ml_charger_event_callback)(ml_charger_event);

static ml_charger_event_callback callback = 0;

void ml_charger_set_event_callback(
    ml_charger_event_callback new_callback
) {
    callback = new_callback;
}

void ml_charger_emit_event(ml_charger_event event) {
    if (callback) {
        callback(event);
    }
}
