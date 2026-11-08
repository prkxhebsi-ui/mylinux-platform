#ifndef MYLINUX_SYMBOL_H
#define MYLINUX_SYMBOL_H

#include <stdint.h>

#define MYLINUX_SYMBOL_ABI_VERSION 1

enum mylinux_symbol_type {
    MYLINUX_SYMBOL_FUNCTION = 1,
    MYLINUX_SYMBOL_OBJECT,
    MYLINUX_SYMBOL_SYSCALL,
    MYLINUX_SYMBOL_FEATURE
};

struct mylinux_symbol {
    const char *name;
    const char *version;
    uint64_t id;
    uint32_t type;
    uint32_t flags;
};

#define MYLINUX_SYMBOL(name_, version_, id_, type_, flags_) \
    const struct mylinux_symbol mylinux_symbol_##name_ \
    __attribute__((used, section(".rodata.mylinux.symbols"))) = { \
        #name_, version_, id_, type_, flags_ \
    }

#endif
