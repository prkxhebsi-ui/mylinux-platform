/*
 * Charger IC integration point.
 *
 * A selected charger IC is responsible for its documented
 * charging regulation and safety functions.
 *
 * This file intentionally provides no generic charge-enable,
 * voltage-programming or current-programming operation.
 */

int ml_charger_ic_backend_available(void) {
    return 0;
}
