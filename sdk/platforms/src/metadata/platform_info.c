#include "platform_info.h"

int sdk_platform_info_valid(const struct sdk_platform_info *info)
{
    if (!info)
        return 0;

    if (info->api_level < 1 || info->major < 0 || info->minor < 0)
        return 0;

    if (info->major > 999 || info->minor > 999)
        return 0;

    return 1;
}
