#!/bin/sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/../../../.." && pwd)"
CONFIG="$ROOT_DIR/build/make/config/mylinux_config.mk"
PRODUCT="$ROOT_DIR/build/make/target/product/mylinux/mylinux_base.mk"

if [ ! -f "$CONFIG" ]; then
    echo "ERROR: Missing MyLinux build configuration: $CONFIG" >&2
    exit 1
fi

if [ ! -f "$PRODUCT" ]; then
    echo "ERROR: Missing MyLinux product configuration: $PRODUCT" >&2
    exit 1
fi

echo "MyLinux build configuration: PASS"
echo "Platform: MyLinux"
echo "Product: mylinux"
