# MyLinux Device Configuration

This directory contains MyLinux device and platform configuration.

## Layout

- common/ Shared MyLinux device configuration.
- generic/ Generic reference-device configuration.
- products/ Product registration and product definitions.

## Rules

- Preserve existing AOSP build files.
- Keep device-specific configuration separate from shared platform code.
- Do not enable unverified hardware services.
- Do not include experimental configuration in production builds.
