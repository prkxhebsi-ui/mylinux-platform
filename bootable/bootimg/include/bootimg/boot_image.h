#ifndef MYLINUX_BOOT_IMAGE_H
#define MYLINUX_BOOT_IMAGE_H

#include <cstdint>
#include <string>

namespace mylinux {
namespace bootimg {

struct BootImageInfo {
    std::string name;
    std::string command_line;

    uint32_t header_version = 0;
    uint32_t page_size = 0;

    uint32_t kernel_size = 0;
    uint32_t ramdisk_size = 0;
    uint32_t second_size = 0;
    uint32_t dtb_size = 0;
    uint32_t recovery_dtbo_size = 0;

    uint64_t kernel_offset = 0;
    uint64_t ramdisk_offset = 0;
    uint64_t second_offset = 0;
    uint64_t dtb_offset = 0;
    uint64_t recovery_dtbo_offset = 0;

    uint64_t file_size = 0;
    bool valid = false;
};

bool inspect_file(const std::string& path, BootImageInfo& info);
bool verify_file(const std::string& path);

} // namespace bootimg
} // namespace mylinux

#endif
