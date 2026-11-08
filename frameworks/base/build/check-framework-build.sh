#!/data/data/com.termux/files/usr/bin/bash
set -eu

ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"

echo "Checking MyLinux framework build..."

missing=0

for cmd in javac jar d8 cat rmdir mkdir; do
    if command -v "$cmd" >/dev/null 2>&1; then
        echo "[OK] $cmd"
    else
        echo "[MISSING] $cmd"
        missing=1
    fi
done

if [ -d "$ROOT/frameworks/base/core/java" ]; then
    count=$(find "$ROOT/frameworks/base/core/java" -type f -name '*.java' | wc -l)
    echo "Framework Java files: $count"
else
    echo "Framework source directory missing."
    missing=1
fi

if [ -d "$ROOT/frameworks/base/services/core/java" ]; then
    count=$(find "$ROOT/frameworks/base/services/core/java" -type f -name '*.java' | wc -l)
    echo "Services Java files: $count"
else
    echo "Services source directory missing."
    missing=1
fi

if [ "$missing" -ne 0 ]; then
    echo "Some required build tools or directories are missing."
    exit 1
fi

echo "Tool check complete."
echo "Source and dependency completeness still needs verification."
