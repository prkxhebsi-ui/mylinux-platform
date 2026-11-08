#!/data/data/com.termux/files/usr/bin/sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
cd "$SCRIPT_DIR"

CC="${CC:-clang}"
OUT="${OUT:-build}"

mkdir -p "$OUT"

"$CC" -std=c11 -Wall -Wextra -Werror \
    -Iinclude \
    src/exit.c \
    src/exit_module.c \
    -o "$OUT/exit"

echo "Built: $SCRIPT_DIR/$OUT/exit"
