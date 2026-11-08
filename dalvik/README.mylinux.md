# MyLinux Dalvik Compatibility

This directory contains experimental Dalvik-era compatibility interfaces
and DEX inspection utilities for MyLinux Platform.

## Scope

- Java-side runtime metadata.
- Native DEX header validation.
- A small command-line inspection tool.
- Unit tests for malformed and valid DEX headers.

This is not a complete Dalvik VM implementation. Android application
execution remains the responsibility of the configured Android runtime,
normally ART on modern Android versions.

## Compatibility

The initial native code is intended to be portable C++17. It does not
depend on private ART internals.
