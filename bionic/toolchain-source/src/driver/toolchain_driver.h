#ifndef MYLINUX_TOOLCHAIN_DRIVER_H
#define MYLINUX_TOOLCHAIN_DRIVER_H

#include <stddef.h>

typedef struct {
    const char *target;
    const char *compiler;
    const char *sysroot;
    const char *output;
    int compile_only;
    int link_only;
    int verbose;
} ToolchainOptions;

int toolchain_validate_options(const ToolchainOptions *options);
int toolchain_run(const ToolchainOptions *options,
                  int argc, char *const argv[]);

#endif
