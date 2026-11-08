# MyLinux Build System

This directory contains MyLinux-specific build extensions.

## Layout

- config/   Platform build configuration
- products/ MyLinux product definitions
- tools/    Build validation and helper utilities
- tests/    Build-system tests

## Integration

MyLinux extensions should reuse the existing AOSP build system
where practical.

Do not replace core AOSP Makefiles or definitions.

Product definitions must be explicitly included by the
appropriate product configuration before they take effect.
