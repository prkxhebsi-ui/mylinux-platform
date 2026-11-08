#!/usr/bin/env bash

set -u

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)" || exit 1
ROOT="$(cd -- "$SCRIPT_DIR/../../.." && pwd)" || exit 1

printf 'MyLinux platform: %s\n\n' "$ROOT"

for path in \
    build/soong \
    build/blueprint \
    build/make \
    system/core/rootdir \
    packages \
    device \
    vendor
do
    if [ -d "$ROOT/$path" ]; then
        printf '[ OK ] %s/\n' "$path"
    else
        printf '[MISS] %s/\n' "$path"
    fi
done

printf '\nAndroid.bp files: '
find "$ROOT" \
    -type d \( -name .git -o -name .repo -o -name out \) -prune \
    -o -type f -name Android.bp -print | wc -l

printf '%s\n' 'Tree inspection complete; no build was performed.'
