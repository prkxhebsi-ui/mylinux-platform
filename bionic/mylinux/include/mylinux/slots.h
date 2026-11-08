#ifndef MYLINUX_SLOTS_H
#define MYLINUX_SLOTS_H

#include <stdint.h>

enum mylinux_slot_relation {
    MYLINUX_SLOT_ALIAS = 1,
    MYLINUX_SLOT_DEPENDS,
    MYLINUX_SLOT_EXCLUDES
};

enum mylinux_slot_state {
    MYLINUX_SLOT_DISABLED = 0,
    MYLINUX_SLOT_ENABLED,
    MYLINUX_SLOT_UNAVAILABLE
};

struct mylinux_slot {
    const char *name;
    uint32_t id;
    uint32_t state;
    uint32_t flags;
};

struct mylinux_slot_relation_entry {
    uint32_t source;
    uint32_t target;
    uint32_t relation;
    uint32_t reserved;
};

#define MYLINUX_SLOT(name_, id_, flags_) \
    const struct mylinux_slot mylinux_slot_##name_ \
    __attribute__((used, section(".rodata.mylinux.slots"))) = { \
        #name_, id_, MYLINUX_SLOT_DISABLED, flags_ \
    }

#define MYLINUX_SLOT_RELATION(name_, source_, target_, relation_) \
    const struct mylinux_slot_relation_entry mylinux_relation_##name_ \
    __attribute__((used, section(".rodata.mylinux.slot_relations"))) = { \
        source_, target_, relation_, 0 \
    }

#endif
