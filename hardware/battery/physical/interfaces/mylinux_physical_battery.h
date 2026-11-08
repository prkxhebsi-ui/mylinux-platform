#ifndef MYLINUX_PHYSICAL_BATTERY_H
#define MYLINUX_PHYSICAL_BATTERY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ML_BATTERY_1S = 1,
    ML_BATTERY_2S = 2,
    ML_BATTERY_3S = 3,
    ML_BATTERY_4S = 4
} ml_battery_topology;

typedef struct {
    uint8_t cell_count;
    uint8_t state_of_charge;
    uint8_t state_of_health;

    uint32_t pack_voltage_mv;
    int32_t pack_current_ma;
    int32_t temperature_mc;

    uint32_t remaining_capacity_mah;
    uint32_t full_capacity_mah;

    uint8_t charging;
    uint8_t discharging;
    uint8_t measurement_valid;
} ml_battery_measurements;

typedef struct {
    uint32_t manufacturer_id;
    uint32_t device_id;
    uint8_t detected;
} ml_battery_identity;

typedef struct {
    int (*initialize)(void *context);
    int (*read_measurements)(
        void *context,
        ml_battery_measurements *measurements
    );
    int (*read_identity)(
        void *context,
        ml_battery_identity *identity
    );
    void *context;
} ml_battery_gauge_operations;

typedef struct {
    ml_battery_topology topology;
    ml_battery_gauge_operations gauge;
    uint8_t initialized;
} ml_battery_device;

int ml_battery_topology_valid(ml_battery_topology topology);

int ml_battery_initialize(ml_battery_device *device);

int ml_battery_read(
    ml_battery_device *device,
    ml_battery_measurements *measurements
);

#ifdef __cplusplus
}
#endif

#endif
