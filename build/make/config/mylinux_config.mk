# MyLinux platform build configuration.
#
# This file defines MyLinux-specific defaults.
# It is not automatically loaded by the AOSP build system.

MYLINUX_PLATFORM_NAME := MyLinux
MYLINUX_PLATFORM_VERSION := 1.0
MYLINUX_BUILD_VARIANT ?= userdebug

MYLINUX_SUPPORTED_ARCHES := arm64 x86_64

# Set to true only when the relevant product and device
# configurations are ready.
MYLINUX_PRODUCT_CONFIGURED := false
