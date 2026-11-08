# Building libcrypto

## Requirements

- Termux or another environment with a compatible Clang compiler
- Ninja
- LLVM archive tools (`llvm-ar`)

## Configure

From this directory:

    ./configure.sh

Override the compiler target if needed:

    TARGET=aarch64-linux-android30 ./configure.sh

## Build

    ninja -f build/build.ninja

Build only the static library:

    ninja -f build/build.ninja libmylinuxcrypto.a

## Run tests manually

The build produces `build/params_test`. It is not executed automatically.
Run it explicitly only when you want to test the parameter API.

## Scope

The initial Ninja graph builds only the parameter API foundation.
Digest, cipher, MAC, KDF, and random APIs are not included in this target yet,
because their current implementation status and dependencies need to be
checked before linking them into the same library.

This is a development scaffold, not a production cryptographic library.
