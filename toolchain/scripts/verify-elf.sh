#!/data/data/com.termux/files/usr/bin/sh
# Inspect an ELF file without executing it.
set -eu

if [ "$#" -ne 1 ] || [ ! -f "$1" ]; then
    echo "Usage: $0 ELF_FILE" >&2
    exit 2
fi

file=$1

echo "--- ELF header ---"
readelf -h "$file"

echo "--- Interpreter ---"
readelf -l "$file" 2>/dev/null | grep 'interpreter' || true

echo "--- Dynamic paths ---"
if readelf -d "$file" 2>/dev/null |
    grep -E '\((RPATH|RUNPATH)\)'; then
    echo "WARNING: embedded RPATH/RUNPATH found" >&2
    exit 1
else
    echo "No RPATH/RUNPATH found"
fi

echo "--- Shared dependencies ---"
readelf -d "$file" 2>/dev/null | grep '(NEEDED)' || true
