/*
 * Per-cell measurement interface.
 * Required for multi-cell pack monitoring.
 */
#include <stdint.h>

int ml_cell_monitor_read_mv(
    void *device_context,
    unsigned int cell_index,
    uint32_t *millivolts
) {
    (void)device_context;
    (void)cell_index;
    (void)millivolts;
    return -1;
}
