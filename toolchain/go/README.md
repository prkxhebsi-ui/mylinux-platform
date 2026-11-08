# MyLinux Go Toolchain

User-facing name: Go Toolchain
Platform: MyLinux
Target: Android ARM64
Architecture: AArch64
Android API target: 30

## Source components

src/cmd/go       Go build command
src/cmd/compile  Go compiler
src/cmd/link     Go linker
src/cmd/asm      Go assembler
src/cmd/dist     Go distribution builder

src/runtime      Go runtime
src/reflect      Reflection implementation
src/internal     Internal Go packages
src/syscall      System call interfaces
src/os           Operating system interfaces
src/crypto       Cryptographic packages
src/encoding     Encoding packages
src/math         Mathematical packages
src/sync         Synchronization packages
src/testing      Testing framework

## Prebuilt tools

Existing Android ARM64 toolchain executables are kept in:

prebuilts/

Do not overwrite existing prebuilts during source development.

## Build configuration

config/android-arm64.mk

## Build policy

1. Keep Go source and compiled binaries separate.
2. Use Android ARM64 as the target architecture.
3. Use the existing prebuilt tools where compatible.
4. Preserve the original Go runtime and standard-library licensing.
5. Test compiler and linker changes independently.
6. Do not claim Android compatibility until runtime tests pass.
