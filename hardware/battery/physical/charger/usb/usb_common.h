#ifndef ML_USB_COMMON_H
#define ML_USB_COMMON_H

#include <stdint.h>

typedef enum {
    ML_USB_UNKNOWN,
    ML_USB_SDP,
    ML_USB_CDP,
    ML_USB_DCP,
    ML_USB_TYPE_C_DEFAULT,
    ML_USB_TYPE_C_1_5A,
    ML_USB_TYPE_C_3A,
    ML_USB_PD
} ml_usb_power_type;

typedef struct {
    ml_usb_power_type type;
    uint32_t advertised_voltage_mv;
    uint32_t advertised_current_ma;
    uint8_t connected;
    uint8_t detection_valid;
} ml_usb_power_information;

#endif
