#!/data/data/com.termux/files/usr/bin/bash

set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"

for path in \
    source/bionic \
    source/libcxx \
    source/libcxxabi \
    source/compiler-rt \
    source/libunwind \
    source/kernel-uapi \
    source/libandroid \
    source/liblog \
    sysroot/usr/include \
    sysroot/usr/lib/aarch64-linux-android
do
    if [ -d "$ROOT/$path" ]; then
        printf '[OK] %s\n' "$path"
    else
        printf '[MISSING] %s\n' "$path"
    fi
done

echo "Directory check complete. This does not verify ABI completeness."
