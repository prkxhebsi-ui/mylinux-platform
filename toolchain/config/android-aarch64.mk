# MyLinux Android ARM64 target defaults.
# Override these variables when building for a different Android API.

MYLINUX_TARGET ?= aarch64-linux-android30
MYLINUX_CFLAGS ?= -Wall -Wextra -Werror
MYLINUX_C_STANDARD ?= c11

# Keep this empty unless a specific target library directory is required.
MYLINUX_EXTRA_LDFLAGS ?=

# Android dynamic linker for ARM64.
MYLINUX_DYNAMIC_LINKER ?= /system/bin/linker64
