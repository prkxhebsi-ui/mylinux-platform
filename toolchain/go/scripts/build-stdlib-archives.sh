#!/data/data/com.termux/files/usr/bin/bash

set -eu

ROOT="$HOME/roms/mylinux-platform"
GO_BIN="$(command -v go)"

if [ -z "$GO_BIN" ]; then
    echo "ERROR: Go compiler not found."
    exit 1
fi

echo "Using compiler:"
"$GO_BIN" version

build_target() {
    TARGET_OS="$1"
    TARGET_ARCH="$2"
    TARGET_NAME="${TARGET_OS}_${TARGET_ARCH}"

    DEST="$ROOT/prebuilts/go/pkg/$TARGET_NAME"
    ARCHIVE_DIR="$DEST/archive"
    IMPORTCFG_DIR="$DEST/importcfg"

    mkdir -p "$ARCHIVE_DIR" "$IMPORTCFG_DIR"

    LIST_FILE="$DEST/.export-list.tmp"
    IMPORTCFG="$IMPORTCFG_DIR/stdlib.importcfg"

    echo
    echo "===================================="
    echo "Building Go standard library"
    echo "Target: $TARGET_NAME"
    echo "===================================="

    if ! env \
        GOOS="$TARGET_OS" \
        GOARCH="$TARGET_ARCH" \
        CGO_ENABLED=0 \
        GOTOOLCHAIN=local \
        GOFLAGS= \
        "$GO_BIN" list -export \
        -f '{{if .Export}}{{.ImportPath}}|{{.Export}}{{end}}' \
        std > "$LIST_FILE"; then

        echo "ERROR: Standard library compilation failed."
        rm -f "$LIST_FILE"
        return 1
    fi

    : > "$IMPORTCFG"

    COUNT=0

    while IFS='|' read -r IMPORT_PATH EXPORT_FILE; do
        [ -n "$IMPORT_PATH" ] || continue

        if [ ! -f "$EXPORT_FILE" ]; then
            echo "WARNING: Missing archive for $IMPORT_PATH"
            continue
        fi

        OUTPUT="$ARCHIVE_DIR/$IMPORT_PATH.a"

        mkdir -p "$(dirname "$OUTPUT")"

        cp "$EXPORT_FILE" "$OUTPUT"

        printf 'packagefile %s=%s\n' \
            "$IMPORT_PATH" "$OUTPUT" >> "$IMPORTCFG"

        COUNT=$((COUNT + 1))

    done < "$LIST_FILE"

    rm -f "$LIST_FILE"

    cat > "$DEST/metadata.txt" <<META
Go version: $("$GO_BIN" version)
GOOS: $TARGET_OS
GOARCH: $TARGET_ARCH
CGO_ENABLED: 0
Package count: $COUNT
Origin: Termux Go compiler standard library
META

    echo "Generated archives: $COUNT"
    echo "Archive directory: $ARCHIVE_DIR"
    echo "Import configuration: $IMPORTCFG"
}

build_target android arm64
build_target linux amd64

echo
echo "===================================="
echo "GO ARCHIVE BUILD COMPLETE"
echo "===================================="
