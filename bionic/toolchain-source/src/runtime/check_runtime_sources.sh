#!/data/data/com.termux/files/usr/bin/sh
set -eu

REPO="${1:-.}"
cd "$REPO"

echo "=== Runtime source availability ==="

for path in \
    bionic/libmylinux \
    bionic/libc \
    bionic/linker \
    bionic/linker64 \
    external/zlib \
    external/libarchive \
    external/libcxx \
    frameworks/native/vulkan
do
    if [ -e "$path" ]; then
        printf 'FOUND   %s\n' "$path"
    else
        printf 'MISSING %s\n' "$path"
    fi
done

echo
echo "=== Toolchain ==="
command -v clang || true
command -v clang++ || true
command -v ld.lld || true
command -v llvm-ar || true

echo
echo "=== Existing runtime libraries ==="
for name in \
    ld-android.so libvulkan.so zlib.so libz.so \
    libarchive.so libc.so libc++.so libmylinux.so
do
    find prebuilts/needed/for/root -type f -name "$name" -print 2>/dev/null
done

echo
echo "Checks complete; no libraries were built or modified."
