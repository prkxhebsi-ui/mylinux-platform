#include <stddef.h>
#include <string.h>

struct sdk_api_entry {
    const char *name;
    const char *signature;
};

int sdk_api_compare(const struct sdk_api_entry *old_api,
                    size_t old_count,
                    const struct sdk_api_entry *new_api,
                    size_t new_count,
                    size_t *removed,
                    size_t *changed)
{
    if ((!old_api && old_count) || (!new_api && new_count))
        return -1;

    size_t missing = 0;
    size_t modified = 0;

    for (size_t i = 0; i < old_count; ++i) {
        size_t j;

        for (j = 0; j < new_count; ++j) {
            if (old_api[i].name && new_api[j].name &&
                strcmp(old_api[i].name, new_api[j].name) == 0)
                break;
        }

        if (j == new_count) {
            ++missing;
        } else if (!old_api[i].signature || !new_api[j].signature ||
                   strcmp(old_api[i].signature,
                          new_api[j].signature) != 0) {
            ++modified;
        }
    }

    if (removed)
        *removed = missing;
    if (changed)
        *changed = modified;

    return 0;
}
