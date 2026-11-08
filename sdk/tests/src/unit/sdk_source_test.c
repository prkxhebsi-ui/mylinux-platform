#include <assert.h>
#include <stddef.h>

struct sdk_platform_info {
    int api_level;
    int major;
    int minor;
};

int sdk_platform_info_valid(const struct sdk_platform_info *);
int sdk_ndk_argument_safe(const char *);
int sdk_artifact_path_valid(const char *);

int main(void)
{
    struct sdk_platform_info valid = {30, 1, 0};
    struct sdk_platform_info invalid = {0, 1, 0};

    assert(sdk_platform_info_valid(&valid));
    assert(!sdk_platform_info_valid(&invalid));

    assert(sdk_ndk_argument_safe("-O2"));
    assert(!sdk_ndk_argument_safe("hello;reboot"));

    assert(sdk_artifact_path_valid("lib/libexample.so"));
    assert(!sdk_artifact_path_valid("../outside"));

    return 0;
}
