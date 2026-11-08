# MyLinux Cuttlefish Device Tree

This directory contains a development scaffold for an Android
Cuttlefish-style virtual device.

## Components

- common: shared device configuration
- host: host-side virtual device support
- guest: guest Android configuration
- shared: shared interfaces and resources
- config: virtual hardware configuration
- init: guest initialization prototypes
- manifest: virtual hardware declarations
- product: product definitions
- tests: device tests
- vsoc_x86_64: x86-64 virtual device
- vsoc_arm64: ARM64 virtual device
- vsoc_x86: 32-bit x86 virtual device
- vsoc_riscv64: RISC-V 64-bit experimental target

This is a MyLinux development scaffold, not a complete
AOSP Cuttlefish implementation.
