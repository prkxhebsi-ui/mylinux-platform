#include "mylinux/build_util.h"

#include <assert.h>
#include <string.h>

int main(void)
{
    assert(mylinux_build_name_valid("system_image"));
    assert(mylinux_build_name_valid("arm64-v8a"));
    assert(!mylinux_build_name_valid(""));
    assert(!mylinux_build_name_valid("9invalid"));
    assert(!mylinux_build_name_valid("bad/name"));

    assert(mylinux_build_relative_path_valid("system/bin/init"));
    assert(mylinux_build_relative_path_valid("out/image.img"));
    assert(!mylinux_build_relative_path_valid("/system/bin/init"));
    assert(!mylinux_build_relative_path_valid("../outside"));
    assert(!mylinux_build_relative_path_valid("system/../outside"));
    assert(!mylinux_build_relative_path_valid("system//init"));

    assert(mylinux_build_target_valid("aarch64", "android"));
    assert(mylinux_build_target_valid("riscv64", "linux"));
    assert(!mylinux_build_target_valid("unknown", "android"));
    assert(!mylinux_build_target_valid("aarch64", "unknown"));

    assert(mylinux_build_host_os() != NULL);
    assert(strlen(mylinux_build_host_os()) != 0);

    return 0;
}
