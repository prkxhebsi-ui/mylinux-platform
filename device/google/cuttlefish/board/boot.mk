# MyLinux boot configuration
# This is not a real bootloader implementation.

TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true

MYLINUX_BOOT_ANIMATION := true
MYLINUX_BOOT_ENTRY := boot/animation.py
MYLINUX_BOOT_MANAGER := host/main.py
