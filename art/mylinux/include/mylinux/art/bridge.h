#ifndef MYLINUX_ART_BRIDGE_H
#define MYLINUX_ART_BRIDGE_H

#include <stdint.h>
#include <mylinux/art/status.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t abi_version;
    uint32_t structure_size;
    void *(*allocate)(uint64_t size);
    void (*deallocate)(void *pointer);
} art_mylinux_bridge_t;

art_status_t art_mylinux_bridge_register(
    const art_mylinux_bridge_t *bridge);

const art_mylinux_bridge_t *art_mylinux_bridge_get(void);

#ifdef __cplusplus
}
#endif

#endif
