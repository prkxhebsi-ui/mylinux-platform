#include "bootimg/boot_image.h"

#include <fstream>

namespace mylinux {
namespace bootimg {

bool inspect_file(const std::string& path, BootImageInfo& info) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        info.valid = false;
        return false;
    }

    char magic[8] = {};
    file.read(magic, sizeof(magic));

    if (file.gcount() != sizeof(magic)) {
        info.valid = false;
        return false;
    }

    info.name = path;
    info.valid = true;
    return true;
}

bool verify_file(const std::string& path) {
    BootImageInfo info;
    return inspect_file(path, info);
}

} // namespace bootimg
} // namespace mylinux
