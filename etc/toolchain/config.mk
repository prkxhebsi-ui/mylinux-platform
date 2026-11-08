# MyLinux toolchain defaults
# Runtime paths are intentionally not injected by default.

TARGET_ARCH ?= aarch64
TARGET_OS ?= android
TARGET_API ?= 30

CC ?= clang
CXX ?= clang++
AR ?= llvm-ar
RANLIB ?= llvm-ranlib
STRIP ?= llvm-strip

COMMON_CFLAGS ?= -O2 -Wall -Wextra -Werror
COMMON_LDFLAGS ?=

# Do not put -Wl,-rpath,... or -Wl,-rpath-link,... here.
# Runtime library lookup must be handled by the target environment.
