#!/data/data/com.termux/files/usr/bin/bash
set -eu

ROOT="$HOME/roms/mylinux-platform"
SRC="$ROOT/art/dalvik/libdex"
OUT="$ROOT/prebuilts/lib"

mkdir -p "$OUT"

CLANG="$(command -v clang)"

"$CLANG" \
    --target=aarch64-linux-android30 \
    -std=c11 \
    -O2 \
    -fPIC \
    -shared \
    -Wall \
    -Wextra \
    -Werror \
    -I"$SRC/include" \
    "$SRC/src/DexFile.c" \
    "$SRC/src/DexFormat.c" \
    -Wl,-soname,libdex.so \
    -o "$OUT/libdex.so"

echo "libdex built successfully:"
file "$OUT/libdex.so"
