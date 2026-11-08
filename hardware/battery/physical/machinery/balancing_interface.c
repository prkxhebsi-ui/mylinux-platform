/*
 * Cell-balancing controller integration point.
 *
 * This file deliberately does not activate balancing hardware.
 * A validated, pack-specific balancing implementation is required.
 */
int ml_balancing_backend_available(void) {
    return 0;
}
