#!/usr/bin/env bash
set -u

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)" || exit 1
ROOT="$(cd -- "$SCRIPT_DIR/../../.." && pwd)" || exit 1

errors=0

check_dir() {
    if [ -d "$ROOT/$1" ]; then
        printf '[ OK ] directory: %s\n' "$1"
    else
        printf '[MISS] directory: %s\n' "$1"
        errors=$((errors + 1))
    fi
}

check_file() {
    if [ -f "$ROOT/$1" ]; then
        printf '[ OK ] file:      %s\n' "$1"
    else
        printf '[MISS] file:      %s\n' "$1"
        errors=$((errors + 1))
    fi
}

printf 'MyLinux platform tree check\nRoot: %s\n\n' "$ROOT"

check_dir build
check_dir build/soong
check_dir build/blueprint
check_dir device/mylinux
check_dir vendor/mylinux
check_dir system/core
check_dir kernel

printf '\nBuild entry points:\n'
check_file build/envsetup.sh

printf '\nAndroid.bp files: '
count="$(find "$ROOT" -type d \( -name .git -o -name .repo -o -name out \) -prune -o -type f -name Android.bp -print | wc -l)"
printf '%s\n' "$count"

printf '\nCheck finished: %s missing item(s).\n' "$errors"
printf '%s\n' 'This checks the tree only; it does not verify a successful Soong build.'
