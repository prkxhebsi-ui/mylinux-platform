#ifndef ML_CANONICAL_CHARGER_CONTRACT_H
#define ML_CANONICAL_CHARGER_CONTRACT_H

#include "../../interfaces/charger_driver.h"

/*
 * Canonical read-only charger contract.
 *
 * Hardware-specific implementations must report actual
 * controller measurements and faults.
 */

typedef struct {
    int (*initialize)(void *);
    int (*read_status)(void *, ml_charger_status *);
    int (*read_faults)(void *, uint32_t *);
    void *context;
} ml_canonical_charger_contract;

#endif
