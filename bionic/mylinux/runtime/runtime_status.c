#include <stddef.h>

const char *mylinux_runtime_status(void)
{
    return "MyLinux runtime source present";
}

int mylinux_runtime_ready(void)
{
    return 1;
}
