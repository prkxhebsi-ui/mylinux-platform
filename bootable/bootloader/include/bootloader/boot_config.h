#ifndef MYLINUX_BOOT_CONFIG_H
#define MYLINUX_BOOT_CONFIG_H

#include <string>

namespace mylinux {
namespace bootloader {

struct BootConfig {
    std::string device_name = "gto";
    std::string architecture = "arm64";
    std::string kernel_image;
    std::string ramdisk_image;
    std::string boot_arguments;
    bool verified_boot_required = true;
};

bool validate_config(const BootConfig& config);

} // namespace bootloader
} // namespace mylinux

#endif
