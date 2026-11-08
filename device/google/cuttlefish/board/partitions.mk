# Logical virtual filesystem layout.
# These are NOT physical Android partition sizes.

MYLINUX_ROOT_NAME := c
MYLINUX_SYSTEM_DIR := system
MYLINUX_VENDOR_DIR := vendor
MYLINUX_DATA_DIR := data
MYLINUX_CACHE_DIR := tmp

MYLINUX_VIRTUAL_ROOT := $(MYLINUX_ROOT_NAME)/
MYLINUX_FILESYSTEM := directory-backed
