#include "mylinux/build_util.h"

#include <string.h>

int mylinux_build_target_valid(const char *architecture,
                               const char *operating_system)
{
    static const char *const architectures[] = {
        "aarch64",
        "arm",
        "x86",
        "x86_64",
        "riscv64"
    };

    static const char *const operating_systems[] = {
        "android",
        "linux"
    };

    size_t i;
    int architecture_found = 0;
    int os_found = 0;

    if (architecture == NULL || operating_system == NULL)
        return 0;

    for (i = 0; i < sizeof(architectures) / sizeof(architectures[0]); ++i) {
        if (strcmp(architecture, architectures[i]) == 0) {
            architecture_found = 1;
            break;
        }
    }

    for (i = 0;
         i < sizeof(operating_systems) / sizeof(operating_systems[0]);
         ++i) {
        if (strcmp(operating_system, operating_systems[i]) == 0) {
            os_found = 1;
            break;
        }
    }

    return architecture_found && os_found;
}

const char *mylinux_build_host_os(void)
{
#if defined(__ANDROID__)
    return "android";
#elif defined(__linux__)
    return "linux";
#elif defined(__APPLE__)
    return "darwin";
#elif defined(_WIN32)
    return "windows";
#else
    return "unknown";
#endif
}
