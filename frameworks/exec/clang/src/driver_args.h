#ifndef MYLINUX_DRIVER_ARGS_H
#define MYLINUX_DRIVER_ARGS_H

#include <stddef.h>

#define MYLINUX_MAX_NEEDED 32
#define MYLINUX_MAX_FUNCTIONS 64
#define MYLINUX_PATH_MAX 4096
#define MYLINUX_NAME_MAX 256

enum mylinux_elf_target {
    MYLINUX_ELF_UNSPECIFIED = 0,
    MYLINUX_ELF_LINUX,
    MYLINUX_ELF_ANDROID24,
    MYLINUX_ELF_ANDROID30
};

struct mylinux_driver_args {
    enum mylinux_elf_target target;
    int target_was_set;
    int warnings_as_errors;
    int string_warnings;
    int compile_only;
    int disable_runpath;

    char output[MYLINUX_PATH_MAX];

    char needed[MYLINUX_MAX_NEEDED][MYLINUX_NAME_MAX];
    size_t needed_count;

    char functions[MYLINUX_MAX_FUNCTIONS][MYLINUX_NAME_MAX];
    size_t function_count;
};

void mylinux_driver_args_init(struct mylinux_driver_args *args);

int mylinux_driver_parse(
    int argc,
    char *const argv[],
    struct mylinux_driver_args *args,
    char *error,
    size_t error_size
);

#endif
