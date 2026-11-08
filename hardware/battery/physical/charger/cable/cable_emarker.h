#ifndef ML_CABLE_EMARKER_H
#define ML_CABLE_EMARKER_H

#include <stdint.h>

typedef struct {
    uint32_t vendor_id;
    uint32_t product_id;
    uint32_t cable_current_limit_ma;
    uint32_t cable_voltage_limit_mv;
    uint8_t active_cable;
    uint8_t identity_valid;
} ml_cable_emarker_information;

/* Read information through the USB-C PD controller. */
int ml_cable_emarker_read(
    void *pd_controller,
    ml_cable_emarker_information *information
);

#endif
