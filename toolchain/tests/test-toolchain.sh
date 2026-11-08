#!/data/data/com.termux/files/usr/bin/sh
# Static checks only; does not execute compiled binaries.
set -eu

root=$(CDPATH= cd -- "$(dirname "$0")/../.." && pwd)
cd "$root"

test -f toolchain/README.md
test -f toolchain/config/android-aarch64.mk
test -f toolchain/scripts/mylinux-clang.sh
test -f toolchain/scripts/verify-elf.sh

sh -n toolchain/scripts/mylinux-clang.sh
sh -n toolchain/scripts/verify-elf.sh

grep -q 'aarch64-linux-android30' toolchain/config/android-aarch64.mk
grep -q 'patchelf --remove-rpath' toolchain/scripts/mylinux-clang.sh

echo "Toolchain script checks passed"
