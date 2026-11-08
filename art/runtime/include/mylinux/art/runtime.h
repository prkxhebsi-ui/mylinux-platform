#ifndef MYLINUX_ART_RUNTIME_H
#define MYLINUX_ART_RUNTIME_H

#include <stdint.h>
#include <mylinux/art/status.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ART_RUNTIME_COLD = 0,
    ART_RUNTIME_INITIALIZING,
    ART_RUNTIME_READY,
    ART_RUNTIME_SHUTTING_DOWN,
    ART_RUNTIME_FAILED
} art_runtime_state_t;

typedef struct {
    uint32_t version_major;
    uint32_t version_minor;
    uint32_t version_patch;
    uint64_t feature_mask;
    art_runtime_state_t state;
} art_runtime_info_t;

art_status_t art_runtime_initialize(void);
art_status_t art_runtime_shutdown(void);

art_runtime_state_t art_runtime_get_state(void);
art_status_t art_runtime_get_info(art_runtime_info_t *info);

#ifdef __cplusplus
}
#endif

#endif
