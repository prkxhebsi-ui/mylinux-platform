# Building MyLinux

## Current status

The build process is under development.

There is not yet a guaranteed complete platform build.

## Build environment

Record these details when validating a build:

- Host operating system
- CPU architecture
- Compiler and version
- Android NDK or SDK version, if applicable
- Build system and version
- Target architecture
- Build command
- Build result

## Build rules

1. Keep generated files outside source directories.
2. Use `out/` for generated build output.
3. Record compiler warnings and errors.
4. Never treat a successful object compilation as proof
   that the complete platform can boot.
