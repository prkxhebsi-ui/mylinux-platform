#include "systemd.h"

#include <stdio.h>
#include <unistd.h>

int sd_android_check(void)
{
    static const char *paths[] = {
        "/system/bin/vold",
        "/system/bin/surfaceflinger",
        "/system/bin/servicemanager",
        "/system/bin/app_process64",
        "/system/bin/logd"
    };

    int missing = 0;

    puts("MyLinux Android compatibility check");

    for (size_t i = 0; i < sizeof(paths) / sizeof(paths[0]); i++) {
        if (access(paths[i], X_OK) == 0)
            printf("[FOUND]   %s\n", paths[i]);
        else {
            printf("[MISSING] %s\n", paths[i]);
            missing++;
        }
    }

    puts("Note: system_server is launched by Zygote,");
    puts("not as an independent native executable.");

    return missing;
}
