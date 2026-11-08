#include "driver_args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int fail(char *error, size_t size, const char *message)
{
    if (error != NULL && size != 0)
        snprintf(error, size, "%s", message);
    return -1;
}

static int copy_value(char *dst, size_t capacity, const char *src)
{
    size_t n;

    if (src == NULL)
        return -1;

    n = strlen(src);
    if (n == 0 || n >= capacity)
        return -1;

    memcpy(dst, src, n + 1);
    return 0;
}

static int parse_yes_no(const char *value, int *result)
{
    if (strcmp(value, "yes") == 0) {
        *result = 1;
        return 0;
    }

    if (strcmp(value, "no") == 0) {
        *result = 0;
        return 0;
    }

    return -1;
}

static int set_target(
    struct mylinux_driver_args *args,
    enum mylinux_elf_target target,
    int enabled,
    char *error,
    size_t error_size)
{
    if (!enabled) {
        if (args->target_was_set && args->target == target)
            args->target_was_set = 0;
        return 0;
    }

    if (args->target_was_set && args->target != target)
        return fail(error, error_size,
                    "conflicting ELF target flags");

    args->target = target;
    args->target_was_set = 1;
    return 0;
}

static int add_list(
    const char *value,
    char destination[][MYLINUX_NAME_MAX],
    size_t *count,
    size_t capacity,
    char *error,
    size_t error_size)
{
    const char *start = value;
    const char *p = value;

    if (*value == '\0')
        return fail(error, error_size, "empty list value");

    for (;;) {
        if (*p == ',' || *p == '\0') {
            size_t length = (size_t)(p - start);
            char item[MYLINUX_NAME_MAX];
            size_t i;

            if (length == 0 || length >= sizeof(item))
                return fail(error, error_size,
                            "invalid or oversized list item");

            if (*count >= capacity)
                return fail(error, error_size,
                            "list capacity exceeded");

            memcpy(item, start, length);
            item[length] = '\0';

            for (i = 0; i < length; ++i) {
                unsigned char c = (unsigned char)item[i];

                if (!(isalnum(c) || c == '_' || c == '-' ||
                      c == '.' || c == '$'))
                    return fail(error, error_size,
                                "invalid character in list item");
            }

            for (i = 0; i < *count; ++i) {
                if (strcmp(destination[i], item) == 0)
                    return fail(error, error_size,
                                "duplicate list item");
            }

            memcpy(destination[*count], item, length + 1);
            ++(*count);

            if (*p == '\0')
                break;

            start = p + 1;
        }

        if (*p == '\0')
            break;

        ++p;
    }

    return 0;
}

void mylinux_driver_args_init(struct mylinux_driver_args *args)
{
    if (args != NULL)
        memset(args, 0, sizeof(*args));
}

int mylinux_driver_parse(
    int argc,
    char *const argv[],
    struct mylinux_driver_args *args,
    char *error,
    size_t error_size)
{
    int i;

    if (args == NULL || argv == NULL)
        return fail(error, error_size, "invalid parser arguments");

    if (error != NULL && error_size != 0)
        error[0] = '\0';

    mylinux_driver_args_init(args);

    for (i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        const char *value;
        int enabled;

        if (strcmp(arg, "--Werror") == 0) {
            args->warnings_as_errors = 1;
            continue;
        }

        if (strcmp(arg, "--Wstring") == 0) {
            args->string_warnings = 1;
            continue;
        }

        if (strcmp(arg, "-c") == 0) {
            args->compile_only = 1;
            continue;
        }

        if (strncmp(arg, "--linux-elf=", 12) == 0) {
            value = arg + 12;
            if (parse_yes_no(value, &enabled) != 0)
                return fail(error, error_size,
                            "--linux-elf expects yes or no");
            if (set_target(args, MYLINUX_ELF_LINUX, enabled,
                           error, error_size) != 0)
                return -1;
            continue;
        }

        if (strncmp(arg, "--android30-elf=", 16) == 0) {
            value = arg + 16;
            if (parse_yes_no(value, &enabled) != 0)
                return fail(error, error_size,
                            "--android30-elf expects yes or no");
            if (set_target(args, MYLINUX_ELF_ANDROID30, enabled,
                           error, error_size) != 0)
                return -1;
            continue;
        }

        if (strncmp(arg, "--android24-elf=", 16) == 0) {
            value = arg + 16;
            if (parse_yes_no(value, &enabled) != 0)
                return fail(error, error_size,
                            "--android24-elf expects yes or no");
            if (set_target(args, MYLINUX_ELF_ANDROID24, enabled,
                           error, error_size) != 0)
                return -1;
            continue;
        }

        if (strncmp(arg, "--disable-runpath=", 18) == 0) {
            if (parse_yes_no(arg + 18, &args->disable_runpath) != 0)
                return fail(error, error_size,
                            "--disable-runpath expects yes or no");
            continue;
        }

        if (strcmp(arg, "-o") == 0) {
            if (++i >= argc)
                return fail(error, error_size, "-o requires a filename");

            if (copy_value(args->output, sizeof(args->output),
                           argv[i]) != 0)
                return fail(error, error_size,
                            "invalid or oversized output filename");
            continue;
        }

        if (strncmp(arg, "--add-needed-libs=", 18) == 0) {
            if (add_list(arg + 18, args->needed, &args->needed_count,
                         MYLINUX_MAX_NEEDED, error, error_size) != 0)
                return -1;
            continue;
        }

        if (strncmp(arg, "--add-FUNC=", 11) == 0) {
            if (add_list(arg + 11, args->functions,
                         &args->function_count, MYLINUX_MAX_FUNCTIONS,
                         error, error_size) != 0)
                return -1;
            continue;
        }

        if (arg[0] == '-')
            return fail(error, error_size, "unknown driver option");

        /*
         * Input filenames are currently accepted but not stored.
         * The next layer should add a bounded input-file array.
         */
    }

    if (args->compile_only && args->output[0] == '\0')
        return fail(error, error_size,
                    "-c requires an explicit -o output in this driver");

    return 0;
}
