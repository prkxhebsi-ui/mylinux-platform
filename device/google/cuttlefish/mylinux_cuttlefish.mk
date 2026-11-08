MYLINUX_CUTTLEFISH_PATH := device/google/cuttlefish

PRODUCT_NAME := mylinux_cuttlefish
PRODUCT_DEVICE := mylinux_cuttlefish
PRODUCT_BRAND := MyLinux
PRODUCT_MODEL := MyLinux Homemade Cuttlefish
PRODUCT_MANUFACTURER := MyLinux

PRODUCT_CHARACTERISTICS := tablet

MYLINUX_BUILD_TYPE := native-manager
MYLINUX_EMULATOR_ENABLED := false
MYLINUX_KVM_REQUIRED := false
MYLINUX_QEMU_REQUIRED := false

include $(MYLINUX_CUTTLEFISH_PATH)/device.mk
include $(MYLINUX_CUTTLEFISH_PATH)/product/base.mk
include $(MYLINUX_CUTTLEFISH_PATH)/product/packages.mk
include $(MYLINUX_CUTTLEFISH_PATH)/product/system_properties.mk
include $(MYLINUX_CUTTLEFISH_PATH)/product/security.mk
include $(MYLINUX_CUTTLEFISH_PATH)/product/locale.mk
include $(MYLINUX_CUTTLEFISH_PATH)/product/debug.mk
