#include <stdint.h>

typedef struct {
    uint32_t communication_errors;
    uint32_t detection_errors;
    uint32_t controller_errors;
    uint32_t invalid_status_reads;
} ml_charger_diagnostics;

void ml_charger_diagnostics_reset(
    ml_charger_diagnostics *diagnostics
) {
    if (!diagnostics) return;

    diagnostics->communication_errors = 0;
    diagnostics->detection_errors = 0;
    diagnostics->controller_errors = 0;
    diagnostics->invalid_status_reads = 0;
}
