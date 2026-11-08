#!/bin/sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
ROOT_DIR="$(CDPATH= cd -- "$SCRIPT_DIR/../../../../.." && pwd)"

"$ROOT_DIR/build/make/tools/mylinux/check_config.sh"

grep -q '^MYLINUX_PLATFORM_NAME := MyLinux$' \
    "$ROOT_DIR/build/make/config/mylinux_config.mk"

grep -q '^MYLINUX_PRODUCT_NAME := mylinux$' \
    "$ROOT_DIR/build/make/target/product/mylinux/mylinux_base.mk"

echo "MyLinux build configuration tests: PASS"
