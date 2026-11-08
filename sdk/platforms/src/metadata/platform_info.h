#ifndef MYLINUX_PLATFORM_INFO_H
#define MYLINUX_PLATFORM_INFO_H

struct sdk_platform_info {
    int api_level;
    int major;
    int minor;
};

int sdk_platform_info_valid(const struct sdk_platform_info *info);

#endif
