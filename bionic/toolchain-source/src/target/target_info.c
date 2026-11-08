#include "target_info.h"

#include <string.h>

static const ToolchainTarget targets[] = {
    {
        "aarch64-linux-android30",
        "aarch64",
        "android",
        30U,
        64U
    }
};

const ToolchainTarget *toolchain_find_target(const char *triple)
{
    if (triple == NULL) {
        return NULL;
    }

    for (unsigned long i = 0;
         i < sizeof(targets) / sizeof(targets[0]); ++i) {
        if (strcmp(targets[i].triple, triple) == 0) {
            return &targets[i];
        }
    }

    return NULL;
}
