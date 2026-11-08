#!/usr/bin/env bash

cat <<'HELP'
MyLinux Soong helper commands
=============================

soong-env.sh
    Source it from Bash to set platform environment variables.

soong-list-bp.sh
    Find Android.bp files in the MyLinux platform tree.

soong-check.sh
    Check expected directories and the build entry point.

soong-help.sh
    Display this help.

Examples:
    source build/soong/mylinux/scripts/soong-env.sh
    bash build/soong/mylinux/scripts/soong-list-bp.sh
    bash build/soong/mylinux/scripts/soong-check.sh
    bash build/soong/mylinux/scripts/soong-help.sh

Important:
    These are MyLinux helper scripts, not the actual Soong build system.
    A real Soong build requires compatible Soong source and its dependencies.
HELP
