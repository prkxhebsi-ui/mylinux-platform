# MyLinux Soong

Android-oriented declarative build system.

Responsibilities:
- Android.bp parsing
- Module registration
- Dependency graph construction
- Variant selection
- Compiler and linker configuration
- Ninja build generation
- Incremental builds

Primary implementation language: Go.

The MyLinux extensions must remain separate from
upstream-compatible Soong interfaces.
