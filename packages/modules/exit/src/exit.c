#define _POSIX_C_SOURCE 200809L

#include "exit_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage(const char *name) {
    fprintf(stderr,
        "Usage:\n"
        "  %s CODE\n"
        "  %s --error [STATE_FILE] [LIMIT]\n"
        "  %s --status [STATE_FILE]\n"
        "  %s --reset [STATE_FILE]\n",
        name, name, name, name);
}

int main(int argc, char **argv) {
    const char *state = "/tmp/mylinux-exit-errors";
    unsigned int limit = EXIT_DEFAULT_ERROR_LIMIT;
    int code;

    if (argc == 2 && exit_module_parse_code(argv[1], &code) == 0) {
        return code;
    }

    if (argc >= 2 && strcmp(argv[1], "--error") == 0) {
        int result;

        if (argc >= 3) state = argv[2];

        if (argc >= 4) {
            char *end = NULL;
            unsigned long parsed = strtoul(argv[3], &end, 10);

            if (!end || *end || parsed == 0 || parsed > 1000000) {
                fprintf(stderr, "exit: invalid error limit\n");
                return 2;
            }
            limit = (unsigned int)parsed;
        }

        result = exit_module_report_error(state, limit);

        if (result < 0) {
            perror("exit: recording error");
            return 2;
        }

        if (result == 1) {
            fprintf(stderr, "exit: error threshold reached (%u)\n", limit);
            return 1;
        }

        return 0;
    }

    if (argc >= 2 && strcmp(argv[1], "--status") == 0) {
        unsigned int count;

        if (argc >= 3) state = argv[2];

        if (exit_module_read_errors(state, &count) < 0) {
            perror("exit: reading error count");
            return 2;
        }

        printf("%u\n", count);
        return 0;
    }

    if (argc >= 2 && strcmp(argv[1], "--reset") == 0) {
        const char *path = argc >= 3 ? argv[2] : state;
        FILE *file = fopen(path, "w");

        if (!file) {
            perror("exit: resetting error count");
            return 2;
        }

        if (fputs("0\n", file) == EOF || fclose(file) != 0) {
            perror("exit: writing reset");
            return 2;
        }

        return 0;
    }

    usage(argv[0]);
    return 2;
}
