#ifndef MYLINUX_BUILD_UTIL_H
#define MYLINUX_BUILD_UTIL_H

#include <stddef.h>

int mylinux_build_name_valid(const char *name);
int mylinux_build_relative_path_valid(const char *path);
int mylinux_build_write_all(int fd, const void *data, size_t size);
int mylinux_build_target_valid(const char *architecture,
                               const char *operating_system);
const char *mylinux_build_host_os(void);

#endif
