#!/data/data/com.termux/files/usr/bin/sh
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
cd "$ROOT"

CC=${CC:-clang}
AR=${AR:-llvm-ar}
TARGET=${TARGET:-aarch64-linux-android30}
BUILD_DIR=${BUILD_DIR:-build}

command -v "$CC" >/dev/null 2>&1 || {
    echo "configure: compiler not found: $CC" >&2
    exit 1
}
command -v ninja >/dev/null 2>&1 || {
    echo "configure: ninja not found; install it with pkg install ninja" >&2
    exit 1
}

mkdir -p "$BUILD_DIR"

cat > "$BUILD_DIR/build.ninja" <<NINJA
cc = $CC
ar = $AR
target = $TARGET
cflags = --target=\$target -std=c11 -O2 -Wall -Wextra -Wpedantic -fPIC -D_GNU_SOURCE -I$ROOT/include -I$ROOT/src/crypto -I$ROOT/src/digest -I$ROOT/src/cipher -I$ROOT/src/mac -I$ROOT/src/random
ldflags =

rule cc
  command = \$cc \$cflags -MMD -MF \$out.d -c \$in -o \$out
  depfile = \$out.d
  deps = gcc
  description = CC \$out

rule archive
  command = rm -f \$out && \$ar rcs \$out \$in
  description = AR \$out

rule link_test
  command = \$cc --target=\$target \$in -o \$out
  description = LINK \$out

build obj/params.o: cc src/crypto/params.c
build obj/param_build.o: cc src/crypto/param_build.c
build obj/lib_ctx.o: cc src/crypto/lib_ctx.c

build libmylinuxcrypto.a: archive obj/params.o obj/param_build.o obj/lib_ctx.o

build obj/params_test.o: cc tests/params_test.c
build params_test: link_test obj/params_test.o libmylinuxcrypto.a

build all: phony libmylinuxcrypto.a params_test
default all
NINJA

printf 'Configured: %s/build.ninja\n' "$BUILD_DIR"
printf 'Target: %s\n' "$TARGET"
printf 'Generated build files are not staged.\n'
