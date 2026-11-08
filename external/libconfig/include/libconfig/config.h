#ifndef MYLINUX_LIBCONFIG_H
#define MYLINUX_LIBCONFIG_H

#include <stddef.h>

typedef struct {
    char *key;
    char *value;
} lc_entry;

typedef struct {
    lc_entry *entries;
    size_t count;
} lc_config;

int lc_load(lc_config *config, const char *filename);
const char *lc_get(const lc_config *config, const char *key);
void lc_free(lc_config *config);

#endif
