#ifndef MYLINUX_RUNTIME_METADATA_H
#define MYLINUX_RUNTIME_METADATA_H

#include <stdint.h>

#define MYLINUX_ART_METADATA_VERSION 1

enum mylinux_art_metadata_kind {
    MYLINUX_ART_RUNTIME = 1,
    MYLINUX_ART_CLASS,
    MYLINUX_ART_METHOD,
    MYLINUX_ART_SYMBOL,
    MYLINUX_ART_FEATURE
};

struct mylinux_art_metadata {
    const char *name;
    const char *descriptor;
    uint64_t symbol_id;
    uint32_t kind;
    uint32_t version;
    uint32_t flags;
};

#define MYLINUX_ART_METADATA(name_, desc_, id_, kind_, version_, flags_) \
    static const struct mylinux_art_metadata mylinux_art_##name_ \
    __attribute__((used, section(".rodata.mylinux.art"))) = { \
        #name_, desc_, id_, kind_, version_, flags_ \
    }

#endif
