#ifndef MYLINUX_ART_RUNTIME_METADATA_H
#define MYLINUX_ART_RUNTIME_METADATA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ART_METADATA_RUNTIME = 1,
    ART_METADATA_CLASS,
    ART_METADATA_METHOD,
    ART_METADATA_FIELD,
    ART_METADATA_LIBRARY
} art_metadata_kind_t;

typedef struct {
    uint32_t structure_size;
    uint32_t kind;
    uint32_t version;
    uint32_t flags;
    const char *name;
    const char *owner;
} art_metadata_t;

#define ART_METADATA(symbol, type, label, parent) \
    static const art_metadata_t symbol \
    __attribute__((used, section(".rodata.mylinux.art"))) = { \
        sizeof(art_metadata_t), type, 1, 0, label, parent \
    }

#ifdef __cplusplus
}
#endif

#endif
