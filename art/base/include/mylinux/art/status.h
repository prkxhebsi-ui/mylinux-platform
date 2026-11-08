#ifndef MYLINUX_ART_STATUS_H
#define MYLINUX_ART_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ART_STATUS_OK = 0,
    ART_STATUS_INVALID_ARGUMENT,
    ART_STATUS_NOT_INITIALIZED,
    ART_STATUS_ALREADY_INITIALIZED,
    ART_STATUS_OUT_OF_MEMORY,
    ART_STATUS_IO_ERROR,
    ART_STATUS_NOT_SUPPORTED,
    ART_STATUS_INTERNAL_ERROR
} art_status_t;

const char *art_status_string(art_status_t status);

#ifdef __cplusplus
}
#endif

#endif
