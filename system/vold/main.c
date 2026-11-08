#include <stdio.h>
#include <string.h>
#include "mylinux_vold.h"

static void print_usage(const char *program)
{
    printf("Usage: %s [--version | --list | --help]\n", program);
}

int main(int argc, char **argv)
{
    if (argc == 1 || strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
        vold_print_version();
        return 0;
    }

    if (strcmp(argv[1], "--list") == 0) {
        vold_list_volumes();
        return 0;
    }

    fprintf(stderr, "vold: unknown option: %s\n", argv[1]);
    print_usage(argv[0]);
    return 2;
}
