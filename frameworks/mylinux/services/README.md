# MyLinux Services

MyLinux system service architecture.

## Command-line clients

- cmd: service dispatcher
- am: activity and process manager
- pm: package manager
- wm: window manager
- login: user authentication and session client

## Core services

- activity
- package
- window
- login
- power

## Compatibility

The command interfaces aim for Android 11 compatibility.

This implementation is independent of Android's Binder implementation
until Binder integration is added.

Commands must not pretend to perform operations that are not implemented.
Unsupported operations return a clear not-implemented error.
