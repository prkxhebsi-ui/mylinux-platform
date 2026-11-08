# MyLinux platform build configuration.

MYLINUX_PLATFORM_NAME := MyLinux
MYLINUX_PLATFORM_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../../..)

MYLINUX_BUILD_VARIANT ?= eng
MYLINUX_TARGET_ARCH ?= arm64
MYLINUX_TARGET_ARCH_VARIANT ?= armv8-a

MYLINUX_BUILD_VARIANTS := eng userdebug user

ifeq ($(filter $(MYLINUX_BUILD_VARIANT),$(MYLINUX_BUILD_VARIANTS)),)
$(error Unsupported MYLINUX_BUILD_VARIANT: $(MYLINUX_BUILD_VARIANT))
endif
