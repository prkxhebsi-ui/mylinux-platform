#ifndef ML_CUSTOM_SENSOR_TEMPLATE_H
#define ML_CUSTOM_SENSOR_TEMPLATE_H

#include <stdint.h>

int custom_read_pack_voltage(uint32_t *millivolts);
int custom_read_pack_current(int32_t *milliamps);
int custom_read_pack_temperature(int32_t *millicelsius);

#endif
