# Samsung GTO SELinux Policy

Device: Samsung Galaxy Tab A 8.0 (2019)
Codename: gto
Platform: MyLinux
Android compatibility target: Android 11 (SDK 30)

This directory contains device-specific SELinux policy.

Platform policy remains in system/sepolicy.

Existing AOSP Binder types and labels:
- binder_device
- hwbinder_device
- vndbinder_device

Do not duplicate platform type definitions or weaken AOSP neverallow
rules. Add device-specific rules only when required by verified
hardware services and their actual SELinux domains.

Policy compilation and validation must be performed with the
matching Android 11 SELinux build tools.
