# MyLinux Framework Core

Java framework foundation.

## Components

- SystemRuntime: runtime and Android version information.
- SystemProperties: basic property access abstraction.
- SystemService: base class for framework services.
- ServiceRegistry: service registration and lookup.

## Compatibility

These are initial MyLinux-specific classes, not replacements
for Android's existing framework APIs.

Android system-property access will require an Android-specific
backend before these classes can access Android native properties.
