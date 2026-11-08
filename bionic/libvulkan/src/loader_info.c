#include "mylinux_vulkan.h"

/*
 * Loader identification only.
 * This is not a Vulkan implementation and does not expose vk* entrypoints.
 */
const char *mylinux_vulkan_loader_version(void) {
    return "MyLinux Vulkan loader foundation";
}
