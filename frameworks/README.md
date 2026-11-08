# MyLinux Frameworks

The frameworks directory contains the application framework,
system services and native framework components.

## Components

- base/           Core Android framework APIs and services
- native/         Native C/C++ framework libraries
- av/             Audio and video framework
- graphics/       Graphics and rendering infrastructure
- media/          Media playback and codec infrastructure
- network/        Connectivity and network services
- ui/             Input, window and display infrastructure
- runtime/        Java, Kotlin, JNI and native runtime integration
- compatibility/  Android and Linux compatibility layers
- mylinux/        MyLinux-specific framework components
- tests/          Framework tests
- tools/          Framework development utilities

## Architecture

Applications
    |
Framework APIs
    |
System Services
    |
Native Framework Libraries
    |
Android HAL / Linux Kernel

This directory is an evolving framework source tree.
It does not imply that all services are implemented.
