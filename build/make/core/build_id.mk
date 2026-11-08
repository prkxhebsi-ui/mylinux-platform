# Android-style build ID defaults.

ifndef BUILD_ID
BUILD_ID := MYLINUX
endif

ifndef BUILD_NUMBER
BUILD_NUMBER := $(shell date +%Y%m%d%H%M%S)
endif

ifndef BUILD_DATETIME
BUILD_DATETIME := $(shell date +%s)
endif

ifndef BUILD_HOSTNAME
BUILD_HOSTNAME := $(shell hostname 2>/dev/null || echo unknown)
endif
