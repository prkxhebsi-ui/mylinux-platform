#include "libconfig/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *trim(char *s) {
    while (isspace((unsigned char)*s)) s++;

    char *end = s + strlen(s);

    while (end > s && isspace((unsigned char)end[-1]))
        *--end = '\0';

    return s;
}

void lc_free(lc_config *config) {
    if (!config) return;

    for (size_t i = 0; i < config->count; i++) {
        free(config->entries[i].key);
        free(config->entries[i].value);
    }

    free(config->entries);
    config->entries = NULL;
    config->count = 0;
}

const char *lc_get(const lc_config *config, const char *key) {
    if (!config || !key) return NULL;

    for (size_t i = 0; i < config->count; i++) {
        if (strcmp(config->entries[i].key, key) == 0)
            return config->entries[i].value;
    }

    return NULL;
}

int lc_load(lc_config *config, const char *filename) {
    if (!config || !filename) return -1;

    config->entries = NULL;
    config->count = 0;

    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    while ((length = getline(&line, &capacity, file)) != -1) {
        (void)length;

        char *text = trim(line);

        if (*text == '\0' || *text == '#' || *text == ';')
            continue;

        char *equal = strchr(text, '=');
        if (!equal) continue;

        *equal = '\0';

        char *key = trim(text);
        char *value = trim(equal + 1);

        if (*key == '\0') continue;

        size_t value_len = strlen(value);

        if (value_len >= 2 &&
            ((value[0] == '"' && value[value_len - 1] == '"') ||
             (value[0] == '\'' && value[value_len - 1] == '\''))) {
            value[value_len - 1] = '\0';
            value++;
        }

        lc_entry *new_entries = realloc(
            config->entries,
            (config->count + 1) * sizeof(lc_entry)
        );

        if (!new_entries) {
            free(line);
            fclose(file);
            lc_free(config);
            return -1;
        }

        config->entries = new_entries;

        lc_entry *entry = &config->entries[config->count];

        entry->key = strdup(key);
        entry->value = strdup(value);

        if (!entry->key || !entry->value) {
            free(entry->key);
            free(entry->value);
            free(line);
            fclose(file);
            lc_free(config);
            return -1;
        }

        config->count++;
    }

    free(line);
    fclose(file);
    return 0;
}
