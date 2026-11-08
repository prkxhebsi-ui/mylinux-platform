#ifndef MYLINUX_PLATFORM_METADATA_H
#define MYLINUX_PLATFORM_METADATA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Static platform metadata interface.
 *
 * Returned strings are owned by the implementation.
 * Callers must not modify or free them.
 * Unknown keys return NULL.
 */
const char *mylinux_metadata_get(const char *key);

/* Return the number of entries in the static metadata table. */
size_t mylinux_metadata_count(void);

/* Return the metadata interface version. */
unsigned int mylinux_metadata_version(void);

/* Return nonzero when a key is present. */
int mylinux_metadata_has_key(const char *key);

/*
 * Metadata lookup is case-sensitive.
 * Keys must be NUL-terminated strings.
 * A NULL key is treated as absent.
 *
 * The table is immutable after program startup.
 * Concurrent read-only lookups do not mutate shared state.
 *
 * This interface does not establish device identity,
 * runtime health, secure-boot state, or policy enforcement.
 * Those values must be obtained from their authoritative
 * platform services instead of inferred from metadata.
 */

#ifdef __cplusplus
}
#endif

#endif
