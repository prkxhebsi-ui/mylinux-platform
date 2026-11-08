.RECIPEPREFIX := >

MYLINUX_NDK_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
MYLINUX_NDK_SOURCE := $(MYLINUX_NDK_ROOT)/source
MYLINUX_NDK_SYSROOT := $(MYLINUX_NDK_ROOT)/sysroot

MYLINUX_NDK_TARGET := aarch64-linux-android30
MYLINUX_NDK_API := 30
MYLINUX_NDK_ARCH := arm64

MYLINUX_CC ?= clang
MYLINUX_CXX ?= clang++
MYLINUX_AR ?= llvm-ar
MYLINUX_STRIP ?= llvm-strip

MYLINUX_CFLAGS := --target=$(MYLINUX_NDK_TARGET)
MYLINUX_CXXFLAGS := --target=$(MYLINUX_NDK_TARGET)
MYLINUX_LDFLAGS := --target=$(MYLINUX_NDK_TARGET)

.PHONY: ndk-info ndk-check

ndk-info:
>@echo "MyLinux NDK"
>@echo "Target: $(MYLINUX_NDK_TARGET)"
>@echo "Source: $(MYLINUX_NDK_SOURCE)"
>@echo "Sysroot: $(MYLINUX_NDK_SYSROOT)"

ndk-check:
>@test -d "$(MYLINUX_NDK_SOURCE)"
>@test -d "$(MYLINUX_NDK_SYSROOT)"
>@echo "NDK directory structure exists."
