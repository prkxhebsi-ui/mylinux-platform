#include "systemd.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void usage(const char *program)
{
    printf("MyLinux systemd development implementation\n\n");
    printf("Usage:\n");
    printf("  %s --version\n", program);
    printf("  %s --check [unit-directory]\n", program);
    printf("  %s --android-check\n", program);
    printf("  %s --run [unit-directory]\n", program);
}

int main(int argc, char **argv)
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usage(argv[0]);
        return argc < 2 ? 1 : 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
        puts("MyLinux systemd 0.1-development");
        return 0;
    }

    if (strcmp(argv[1], "--android-check") == 0)
        return sd_android_check() ? 1 : 0;

    if (strcmp(argv[1], "--check") == 0 ||
        strcmp(argv[1], "--run") == 0) {
        const char *directory =
            argc >= 3 ? argv[2] : "systemd/units";

        SDUnit *units = sd_load_units(directory);

        if (!units) {
            fprintf(stderr, "systemd: no valid service units loaded\n");
            return 1;
        }

        int result;

        if (strcmp(argv[1], "--check") == 0)
            result = sd_check_units(units);
        else
            result = sd_manager_run(units);

        sd_free_units(units);
        return result ? 1 : 0;
    }

    usage(argv[0]);
    return 1;
}
