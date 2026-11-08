#include "toolchain_driver.h"

int toolchain_validate_options(const ToolchainOptions *options)
{
    if (options == NULL || options->target == NULL ||
        options->target[0] == '\0') {
        return -1;
    }

    if (options->compile_only && options->link_only) {
        return -1;
    }

    return 0;
}

/*
 * Process execution is intentionally not implemented yet.
 * A future driver must construct argv safely and avoid shell evaluation.
 */
int toolchain_run(const ToolchainOptions *options,
                  int argc, char *const argv[])
{
    (void)argc;
    (void)argv;

    if (toolchain_validate_options(options) != 0) {
        return -1;
    }

    return -2;
}
