#ifndef MYLINUX_PLATFORM_METADATA_H
#define MYLINUX_PLATFORM_METADATA_H

#ifdef __cplusplus
extern "C" {
#endif

struct mylinux_platform_metadata {
    const char* name;
    const char* version;
    const char* architecture;
    int api_level;
    unsigned int schema_version;
};

const struct mylinux_platform_metadata*
mylinux_get_platform_metadata(void);

int mylinux_validate_platform_metadata(
    const struct mylinux_platform_metadata* info);

#ifdef __cplusplus
}
#endif

#endif
