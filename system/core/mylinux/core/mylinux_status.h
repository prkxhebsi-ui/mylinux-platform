#ifndef MYLINUX_STATUS_H
#define MYLINUX_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MYLINUX_STATUS_OK = 0,
    MYLINUX_STATUS_ERROR = -1,
    MYLINUX_STATUS_INVALID_ARGUMENT = -2,
    MYLINUX_STATUS_NOT_FOUND = -3,
    MYLINUX_STATUS_PERMISSION_DENIED = -4,
    MYLINUX_STATUS_OUT_OF_MEMORY = -5,
    MYLINUX_STATUS_NOT_SUPPORTED = -6
} mylinux_status_t;

const char *mylinux_status_string(mylinux_status_t status);

#ifdef __cplusplus
}
#endif

#endif
