#include "diagnostics.h"

#include <stdio.h>

void toolchain_error(const char *component, const char *message)
{
    fprintf(stderr, "%s: error: %s\n",
            component != NULL ? component : "toolchain",
            message != NULL ? message : "unknown error");
}

void toolchain_warning(const char *component, const char *message)
{
    fprintf(stderr, "%s: warning: %s\n",
            component != NULL ? component : "toolchain",
            message != NULL ? message : "unspecified warning");
}
