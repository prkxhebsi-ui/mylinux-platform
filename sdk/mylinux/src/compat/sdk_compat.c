#include <stddef.h>

int mylinux_sdk_api_level_supported(int api_level)
{
    return api_level >= 1 && api_level <= 30;
}
