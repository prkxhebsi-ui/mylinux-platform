#!/usr/bin/env bash

# MyLinux Soong helper environment.
# Source this file from Bash; it does not implement Soong itself.

_mylinux_soong_script="${BASH_SOURCE[0]}"
MYLINUX_PLATFORM_ROOT="$(
    cd -- "$(dirname -- "$_mylinux_soong_script")/../../.." &&
    pwd
)" || {
    printf '%s\n' "soong-env: cannot locate platform root" >&2
    unset _mylinux_soong_script
    return 1
}

export MYLINUX_PLATFORM_ROOT
export MYLINUX_SOONG_HELPERS="$MYLINUX_PLATFORM_ROOT/build/soong/mylinux/scripts"

unset _mylinux_soong_script
printf 'MyLinux platform: %s\n' "$MYLINUX_PLATFORM_ROOT"
printf 'Soong helpers:    %s\n' "$MYLINUX_SOONG_HELPERS"
