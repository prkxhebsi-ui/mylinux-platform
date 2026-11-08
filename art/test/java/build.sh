#!/data/data/com.termux/files/usr/bin/bash
set -eu

ROOT="$(cd "$(dirname "$0")" && pwd)"
SRC="$ROOT/src"
OUT="$ROOT/out"
CLASSES="$OUT/classes"
DEX="$OUT/dex"

if ! command -v javac >/dev/null 2>&1; then
    echo "ERROR: javac is not installed."
    exit 1
fi

mkdir -p "$CLASSES" "$DEX"

echo "[1/3] Compiling Java test sources..."

javac \
    -source 8 \
    -target 8 \
    -Xlint:-options \
    -d "$CLASSES" \
    "$SRC/DexArithmeticTest.java" \
    "$SRC/DexArrayTest.java" \
    "$SRC/DexObjectTest.java" \
    "$SRC/DexControlFlowTest.java" \
    "$SRC/DexTestRunner.java" || exit 1

echo "[2/3] Java class files created:"
find "$CLASSES" -type f -name '*.class' -print

D8="${D8:-}"

if [ -z "$D8" ]; then
    D8="$(command -v d8 2>/dev/null || true)"
fi

if [ -z "$D8" ] && [ -d "$HOME/android-sdk/build-tools" ]; then
    for candidate in "$HOME"/android-sdk/build-tools/*/d8; do
        if [ -x "$candidate" ]; then
            D8="$candidate"
        fi
    done
fi

if [ -z "$D8" ]; then
    echo "[3/3] d8 was not found."
    echo "Java compilation succeeded, but DEX generation is pending."
    echo "Install Android SDK Build Tools or set D8=/path/to/d8."
    exit 0
fi

echo "[3/3] Converting Java classes into DEX..."

rm -f "$DEX/classes.dex"

"$D8" \
    --min-api 24 \
    --output "$DEX" \
    "$CLASSES"/*.class || exit 1

if [ ! -s "$DEX/classes.dex" ]; then
    echo "ERROR: DEX output was not created."
    exit 1
fi

echo "DEX generated:"
ls -lh "$DEX/classes.dex"
