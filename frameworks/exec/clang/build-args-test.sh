#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/../../.." && pwd)
BUILD_DIR="$ROOT/build/clang-driver-tests"
CC=${CC:-clang}

mkdir -p "$BUILD_DIR"

"$CC" \
    -std=c11 -Wall -Wextra -Wpedantic -Werror \
    -I"$SCRIPT_DIR/src" \
    "$SCRIPT_DIR/src/driver_args.c" \
    "$SCRIPT_DIR/src/driver_args_test.c" \
    -o "$BUILD_DIR/driver_args_test.new"

mv -f "$BUILD_DIR/driver_args_test.new" "$BUILD_DIR/driver_args_test"
exec "$BUILD_DIR/driver_args_test"
