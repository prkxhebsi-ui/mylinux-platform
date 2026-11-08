# MyLinux Go Toolchain
# Target: Android ARM64

MYLINUX_GOOS := android
MYLINUX_GOARCH := arm64
MYLINUX_GOARM64 := v8.0

MYLINUX_GO_TARGET := android/arm64

# Existing prebuilt toolchain location
MYLINUX_PREBUILTS := $(MYLINUX_ROOT)/prebuilts

# Compiler configuration
MYLINUX_GO_BUILD_MODE := release
MYLINUX_GO_CGO_ENABLED := 0

# Android native target
MYLINUX_ANDROID_API := 30

# Architecture
MYLINUX_TARGET_TRIPLE := aarch64-linux-android

# Source directories
MYLINUX_GO_SRC := $(MYLINUX_ROOT)/toolchain/go/src
MYLINUX_GO_RUNTIME := $(MYLINUX_GO_SRC)/runtime
MYLINUX_GO_COMPILER := $(MYLINUX_GO_SRC)/cmd/compile
MYLINUX_GO_LINKER := $(MYLINUX_GO_SRC)/cmd/link
MYLINUX_GO_ASSEMBLER := $(MYLINUX_GO_SRC)/cmd/asm
