#!/data/data/com.termux/files/usr/bin/bash
set -eu

ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"

MODULE="$ROOT/libcore/dalvik"
OUT="$ROOT/out/java/dalvik-config"
CLASSES="$OUT/classes"
JAR="$ROOT/prebuilts/java/jars/mylinux-dalvik-config.jar"

SOURCE="$MODULE/src/main/java/org/mylinux/dalvik/config/ToolDescriptor.java"

if ! command -v javac >/dev/null 2>&1; then
    echo "ERROR: javac is not installed."
    exit 1
fi

if ! command -v jar >/dev/null 2>&1; then
    echo "ERROR: jar command is not installed."
    exit 1
fi

if [ ! -f "$SOURCE" ]; then
    echo "ERROR: ToolDescriptor.java not found:"
    echo "$SOURCE"
    exit 1
fi

rm -rf "$CLASSES"
mkdir -p "$CLASSES"

echo "[1/4] Compiling Java source..."

javac --release 8 \
    -d "$CLASSES" \
    "$SOURCE"

echo "[2/4] Copying module resources..."

if [ -d "$MODULE/src/main/resources" ]; then
    cp -R "$MODULE/src/main/resources/." "$CLASSES/"
fi

echo "[3/4] Creating JAR..."

mkdir -p "$(dirname "$JAR")"

jar --create \
    --file "$JAR" \
    -C "$CLASSES" .

echo "[4/4] Verifying JAR..."

jar --list --file "$JAR"

echo
echo "Build successful:"
echo "$JAR"
