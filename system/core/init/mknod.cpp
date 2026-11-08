#include "init.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <sys/sysmacros.h>

namespace mylinux {
namespace init {

static bool parseNumber(
    const std::string& text,
    unsigned long& value,
    int base
) {
    if (text.empty()) return false;

    char* end = nullptr;
    errno = 0;

    value = std::strtoul(text.c_str(), &end, base);

    return errno == 0 &&
           end != text.c_str() &&
           *end == '\0';
}

bool executeMknod(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::fprintf(
            stderr,
            "init: mknod PATH TYPE [MAJOR MINOR] [MODE]\n"
        );
        return false;
    }

    const std::string& path = args[1];
    const std::string& type = args[2];

    mode_t mode = 0600;
    dev_t device = 0;

    if (type == "p") {
        mode |= S_IFIFO;

        if (args.size() > 4) return false;

        if (args.size() == 4) {
            unsigned long permissions;

            if (!parseNumber(args[3], permissions, 8) ||
                permissions > 07777) {
                return false;
            }

            mode = S_IFIFO | static_cast<mode_t>(permissions);
        }
    } else {
        if (args.size() < 5 || args.size() > 6) {
            return false;
        }

        unsigned long majorNumber;
        unsigned long minorNumber;

        if (!parseNumber(args[3], majorNumber, 10) ||
            !parseNumber(args[4], minorNumber, 10)) {
            return false;
        }

        if (majorNumber > 0xffffffffUL ||
            minorNumber > 0xffffffffUL) {
            return false;
        }

        if (type == "c") {
            mode |= S_IFCHR;
        } else if (type == "b") {
            mode |= S_IFBLK;
        } else {
            std::fprintf(stderr, "init: invalid mknod type\n");
            return false;
        }

        if (args.size() == 6) {
            unsigned long permissions;

            if (!parseNumber(args[5], permissions, 8) ||
                permissions > 07777) {
                return false;
            }

            mode = (mode & S_IFMT) |
                   static_cast<mode_t>(permissions);
        }

        device = makedev(
            static_cast<unsigned int>(majorNumber),
            static_cast<unsigned int>(minorNumber)
        );
    }

    if (mknod(path.c_str(), mode, device) != 0) {
        std::fprintf(
            stderr,
            "init: mknod %s failed: %s\n",
            path.c_str(),
            std::strerror(errno)
        );
        return false;
    }

    return true;
}

} // namespace init
} // namespace mylinux
