LIBCRYPTO_ROOT := $(call my-dir)

LIBCRYPTO_SRC := \
    $(LIBCRYPTO_ROOT)/src/crypto/version.c \
    $(LIBCRYPTO_ROOT)/src/crypto/error.c \
    $(LIBCRYPTO_ROOT)/src/random/random.c

LIBCRYPTO_INCLUDE := $(LIBCRYPTO_ROOT)/include

LIBCRYPTO_CFLAGS := \
    -std=c11 \
    -Wall \
    -Wextra \
    -fPIC

LIBCRYPTO_TARGET := aarch64-linux-android30

# Digest, cipher and MAC backends are not production-ready.
