#include <stdint.h>

/*
 * Cable attachment is detected by the port controller.
 * This module reports the detected connection.
 */

typedef struct {
    uint8_t attached;
    uint8_t orientation;
    uint8_t cable_type_known;
} ml_cable_connection;

int ml_cable_read_connection(
    void *port_controller,
    ml_cable_connection *connection
) {
    (void)port_controller;
    (void)connection;
    return -1;
}
