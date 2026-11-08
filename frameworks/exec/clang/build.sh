#!/data/data/com.termux/files/usr/bin/sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
REPO_ROOT="$(CDPATH= cd -- "$SCRIPT_DIR/../../.." && pwd)"
cd "$REPO_ROOT"

CC="${CC:-clang}"
OUT="prebuilts/gcc/android/aarch64/bin/clang"
TMP="${OUT}.new"

mkdir -p "$(dirname "$OUT")"

"$CC" -std=c11 -Wall -Wextra -Werror \
    "$SCRIPT_DIR/src/clang.c" \
    -o "$TMP"

chmod 0755 "$TMP"
mv -f "$TMP" "$OUT"

echo "Built MyLinux Clang launcher: $OUT"
