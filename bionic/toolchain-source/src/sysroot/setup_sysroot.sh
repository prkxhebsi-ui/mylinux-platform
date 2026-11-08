#!/data/data/com.termux/files/usr/bin/sh
set -eu

PREFIX="${PREFIX:-/data/data/com.termux/files/usr}"
DEST="${1:-prebuilts/gcc/android/aarch64/sysroot}"

if ! command -v clang >/dev/null 2>&1; then
    echo "error: clang is not installed" >&2
    exit 1
fi

if ! command -v pkg >/dev/null 2>&1; then
    echo "error: Termux pkg command not found" >&2
    exit 1
fi

echo "Termux prefix: $PREFIX"
echo "Sysroot destination: $DEST"
echo
echo "Checking ndk-sysroot package..."

if ! dpkg-query -W -f='${Status}\n' ndk-sysroot 2>/dev/null |
     grep -q 'install ok installed'; then
    echo "ndk-sysroot is not installed."
    echo "Install it with: pkg install ndk-sysroot"
    exit 1
fi

mkdir -p "$DEST/usr/include" "$DEST/usr/lib" \
         "$DEST/usr/lib64" "$DEST/usr/lib/aarch64-linux-android"

echo
echo "Clang resource directory:"
clang --print-resource-dir

echo
echo "Clang Android target include search:"
printf '' | clang --target=aarch64-linux-android30 \
    -v -E -x c - 2>&1 || true

echo
echo "Relevant package-owned paths:"
dpkg-query -L ndk-sysroot 2>/dev/null |
    while IFS= read -r path; do
        case "$path" in
            */include/*|*/lib/*|*/lib64/*|*/lib/aarch64-linux-android/*)
                printf '%s\n' "$path"
                ;;
        esac
    done

echo
echo "Discovery complete."
echo "No headers or libraries were fabricated or copied."
echo "Review the paths above before adding symlinks or copying files."
