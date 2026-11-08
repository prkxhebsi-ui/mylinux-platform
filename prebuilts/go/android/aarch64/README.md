MyLinux Go Toolchain
===================

Target:
  Android ARM64

Target Go identifiers:
  GOOS=android
  GOARCH=arm64

Directories:

bin/
  Go compiler, linker, and tool executables.

pkg/
  Compiled Go packages and package build objects.

lib/
  Go runtime and toolchain support libraries.

lib64/
  ARM64 shared-library support files, when required.

libexec/
  Internal Go toolchain helper executables.

usr/
  Supporting headers, configuration, documentation,
  and other toolchain resources.

Source code is maintained outside prebuilts.
Compiled toolchain artifacts belong here.

Do not place fake compiler binaries or empty package archives here.
