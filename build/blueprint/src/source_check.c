#include "mylinux/build_util.h"

#include <stddef.h>

int mylinux_blueprint_source_name_valid(const char *name)
{
    return mylinux_build_name_valid(name);
}

int mylinux_blueprint_source_path_valid(const char *path)
{
    return mylinux_build_relative_path_valid(path);
}
