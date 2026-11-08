# MyLinux OpenJDK Library Layer (ojluni)

This directory contains the OpenJDK-derived Java library layer for MyLinux.

## Responsibilities

- Java language support
- Core I/O and filesystem APIs
- Collections and utility APIs
- Networking APIs
- Security and cryptography APIs
- Text, locale, and time APIs
- Numeric and NIO APIs

## Source policy

This directory is reserved for real OpenJDK-derived source code and
MyLinux-owned compatibility code.

Do not put placeholder classes into java.* packages and treat them
as a complete Java implementation.

## Build output

Compiled artifacts belong in:

- out/java/ojluni/classes/
- prebuilts/java/ojluni/

The runtime integration is handled by libcore/luni.
