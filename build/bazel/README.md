# MyLinux Bazel Build System

Bazel is an additional build frontend for MyLinux.

## Root configuration

The repository root contains:
- MODULE.bazel
- BUILD.bazel
- .bazelrc

## Directory structure

- rules/cc/       C and C++ build macros
- rules/android/  Android native build macros
- rules/kernel/   Kernel source collection
- rules/mylinux/  MyLinux-specific rules
- platforms/      OS and CPU platform constraints
- toolchains/     Compiler toolchain definitions
- providers/      Shared Starlark providers
- transitions/    Build configuration transitions
- repositories/   External repository definitions
- examples/       Bazel examples

## Sample targets

//tests/sample:libmylinux_base
//tests/sample:mylinux_test

## Current limitations

This is an initial Bazel layer.

It does not yet provide:
- Android NDK toolchain registration
- Automatic Clang discovery
- Kernel Kbuild integration
- Soong-to-Bazel conversion
- Android packaging and image generation
