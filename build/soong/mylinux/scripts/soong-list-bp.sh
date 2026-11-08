#!/usr/bin/env bash
set -u

ROOT="${MYLINUX_PLATFORM_ROOT:-}"

if [ -z "$ROOT" ]; then
    SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)" || exit 1
    ROOT="$(cd -- "$SCRIPT_DIR/../../.." && pwd)" || exit 1
fi

if [ ! -d "$ROOT" ]; then
    printf 'soong-list-bp: root not found: %s\n' "$ROOT" >&2
    exit 1
fi

printf 'Searching for Android.bp files in:\n%s\n\n' "$ROOT"
find "$ROOT" \
    -type d \( -name .git -o -name .repo -o -name out \) -prune \
    -o -type f -name Android.bp -print
