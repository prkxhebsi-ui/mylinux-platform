MYLINUX_CUTTLEFISH_PATH := device/google/cuttlefish

include $(MYLINUX_CUTTLEFISH_PATH)/board/architecture.mk
include $(MYLINUX_CUTTLEFISH_PATH)/board/boot.mk
include $(MYLINUX_CUTTLEFISH_PATH)/board/partitions.mk
include $(MYLINUX_CUTTLEFISH_PATH)/board/kernel.mk
