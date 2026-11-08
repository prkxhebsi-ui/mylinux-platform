#ifndef MYLINUX_PROPERTY_H
#define MYLINUX_PROPERTY_H

#ifdef __cplusplus
extern "C" {
#endif

#define MYLINUX_PROPERTY_NAME_MAX  128
#define MYLINUX_PROPERTY_VALUE_MAX 256

typedef enum {
    MYLINUX_PROPERTY_OK = 0,
    MYLINUX_PROPERTY_ERROR = -1,
    MYLINUX_PROPERTY_INVALID_ARGUMENT = -2,
    MYLINUX_PROPERTY_NOT_FOUND = -3
} mylinux_property_status_t;

/*
 * Validate a property name.
 * This function does not read or modify Android system properties.
 */
mylinux_property_status_t
mylinux_property_validate_name(const char *name);

#ifdef __cplusplus
}
#endif

#endif
