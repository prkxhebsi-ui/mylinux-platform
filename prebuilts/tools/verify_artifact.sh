#!/system/bin/sh
set -eu

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 ARTIFACT" >&2
    exit 2
fi

artifact=$1

if [ ! -f "$artifact" ]; then
    echo "verify_artifact: not a regular file: $artifact" >&2
    exit 1
fi

if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$artifact"
elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$artifact"
else
    echo "verify_artifact: install coreutils or a SHA-256 utility" >&2
    exit 127
fi
