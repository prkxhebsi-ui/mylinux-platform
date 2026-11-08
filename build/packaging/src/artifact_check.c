#include "mylinux/build_util.h"

int mylinux_package_artifact_path_valid(const char *path)
{
    return mylinux_build_relative_path_valid(path);
}
