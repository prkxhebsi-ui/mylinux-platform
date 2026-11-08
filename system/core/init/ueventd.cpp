#include "init.h"

#include <cstdio>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

namespace mylinux {
namespace init {

static bool directoryExists(const char* path) {
    struct stat info {};

    return stat(path, &info) == 0 &&
           S_ISDIR(info.st_mode);
}

static bool pathExists(const char* path) {
    struct stat info {};
    return lstat(path, &info) == 0;
}

static bool ensureSymlink(
    const char* target,
    const char* linkPath
) {
    struct stat info {};

    if (lstat(linkPath, &info) == 0) {
        if (S_ISLNK(info.st_mode)) {
            char buffer[4096];

            ssize_t length = readlink(
                linkPath,
                buffer,
                sizeof(buffer) - 1
            );

            if (length >= 0) {
                buffer[length] = '\0';

                if (std::strcmp(buffer, target) == 0) {
                    return true;
                }
            }
        }

        // Never replace an existing device node or regular file.
        std::fprintf(
            stderr,
            "ueventd: refusing to replace existing path: %s\n",
            linkPath
        );

        return false;
    }

    if (errno != ENOENT) {
        std::perror("ueventd: lstat");
        return false;
    }

    if (symlink(target, linkPath) != 0) {
        std::fprintf(
            stderr,
            "ueventd: cannot create %s -> %s: %s\n",
            linkPath,
            target,
            std::strerror(errno)
        );

        return false;
    }

    return true;
}

static bool createStandardDeviceLinks() {
    if (!directoryExists("/dev")) {
        std::fprintf(stderr, "ueventd: /dev is unavailable\n");
        return false;
    }

    if (!ensureSymlink("/proc/self/fd/0", "/dev/stdin"))
        return false;

    if (!ensureSymlink("/proc/self/fd/1", "/dev/stdout"))
        return false;

    if (!ensureSymlink("/proc/self/fd/2", "/dev/stderr"))
        return false;

    return true;
}

static bool createDeviceTreeLink() {
    const char* target = "/sys/firmware/devicetree/base";
    const char* link = "/proc/device-tree";

    if (!pathExists(target)) {
        puts("ueventd: device tree is unavailable; skipping");
        return true;
    }

    if (pathExists(link)) {
        // Kernel-provided procfs device-tree entries take priority.
        return true;
    }

    return ensureSymlink(target, link);
}

bool initializeUeventd() {
    puts("MyLinux ueventd: initializing");

    if (!directoryExists("/sys")) {
        std::fprintf(stderr, "ueventd: /sys is unavailable\n");
        return false;
    }

    if (!directoryExists("/dev")) {
        std::fprintf(stderr, "ueventd: /dev is unavailable\n");
        return false;
    }

    if (!directoryExists("/sys/devices")) {
        std::fprintf(stderr, "ueventd: /sys/devices is unavailable\n");
        return false;
    }

    if (!createStandardDeviceLinks()) {
        return false;
    }

    if (!createDeviceTreeLink()) {
        return false;
    }

    puts("MyLinux ueventd: initialization checks completed");
    return true;
}

} // namespace init
} // namespace mylinux
