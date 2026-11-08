# MyLinux Static Libraries

Precompiled native static libraries (.a).

host/linux-x86_64:
    Static libraries for Linux x86-64 build tools.

device/arm64:
    Static libraries for Android ARM64 device binaries.

Libraries must be genuine compiled archives.
Do not create empty or placeholder .a files.

Soong integration:
Use cc_prebuilt_library_static for native C/C++
static libraries.

Each library must have the correct architecture,
headers, dependencies and Android ABI.
