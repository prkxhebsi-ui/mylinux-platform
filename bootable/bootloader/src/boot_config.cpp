#include "bootloader/boot_config.h"

namespace mylinux {
namespace bootloader {

bool validate_config(const BootConfig& config) {
    return !config.device_name.empty() &&
           config.architecture == "arm64" &&
           !config.kernel_image.empty() &&
           !config.ramdisk_image.empty();
}

} // namespace bootloader
} // namespace mylinux
