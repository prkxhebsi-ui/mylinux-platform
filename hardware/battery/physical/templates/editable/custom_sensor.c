/* EDITABLE sensor template. */

#include "custom_sensor.h"

int custom_read_pack_voltage(uint32_t *millivolts) {
    (void)millivolts;
    return -1;
}

int custom_read_pack_current(int32_t *milliamps) {
    (void)milliamps;
    return -1;
}

int custom_read_pack_temperature(int32_t *millicelsius) {
    (void)millicelsius;
    return -1;
}
