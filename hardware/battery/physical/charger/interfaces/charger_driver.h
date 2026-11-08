#ifndef MYLINUX_CHARGER_DRIVER_H
#define MYLINUX_CHARGER_DRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ML_CHARGER_NONE = 0,
    ML_CHARGER_USB_LEGACY,
    ML_CHARGER_USB_C,
    ML_CHARGER_USB_PD,
    ML_CHARGER_OTHER
} ml_charger_type;

typedef enum {
    ML_CHARGER_DISCONNECTED = 0,
    ML_CHARGER_CONNECTED,
    ML_CHARGER_CHARGING,
    ML_CHARGER_COMPLETE,
    ML_CHARGER_FAULT
} ml_charger_state;

typedef struct {
    ml_charger_type type;
    ml_charger_state state;

    uint32_t input_voltage_mv;
    uint32_t input_current_ma;

    uint32_t negotiated_voltage_mv;
    uint32_t negotiated_current_ma;

    uint8_t cable_detected;
    uint8_t data_connection;
    uint8_t valid;
} ml_charger_status;

typedef struct {
    int (*initialize)(void *context);
    int (*read_status)(
        void *context,
        ml_charger_status *status
    );
    int (*read_faults)(
        void *context,
        uint32_t *fault_flags
    );
    void *context;
} ml_charger_operations;

typedef struct {
    ml_charger_operations operations;
    uint8_t initialized;
} ml_charger_device;

int ml_charger_initialize(ml_charger_device *device);

int ml_charger_read(
    ml_charger_device *device,
    ml_charger_status *status
);

int ml_charger_read_faults(
    ml_charger_device *device,
    uint32_t *fault_flags
);

#ifdef __cplusplus
}
#endif

#endif
