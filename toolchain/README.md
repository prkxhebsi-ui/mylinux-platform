# MyLinux Toolchain

Toolchain configuration and verification for MyLinux Platform.

## Components

- config/: target and compiler defaults
- scripts/mylinux-clang.sh: compile and optionally remove RPATH/RUNPATH
- scripts/verify-elf.sh: inspect ELF architecture and dynamic paths
- tests/: shell-level toolchain checks

The scripts do not execute the binaries they compile.

RPATH removal is a post-link operation. It does not prevent the linker
from adding a path on subsequent builds, and it does not make a binary
independent of external shared libraries.
