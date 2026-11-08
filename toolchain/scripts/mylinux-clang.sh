#!/data/data/com.termux/files/usr/bin/sh
# Compile a target without executing it.
# Usage: mylinux-clang.sh OUTPUT [CLANG OPTIONS AND SOURCE FILES...]

set -eu

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 OUTPUT SOURCE_OR_OPTIONS..." >&2
    exit 2
fi

output=$1
shift

command -v clang >/dev/null 2>&1 || {
    echo "error: clang not found" >&2
    exit 127
}
command -v readelf >/dev/null 2>&1 || {
    echo "error: readelf not found" >&2
    exit 127
}

outdir=$(dirname "$output")
mkdir -p "$outdir"

# The API level is explicit rather than inherited from Termux's default.
target=${MYLINUX_TARGET:-aarch64-linux-android30}

# Do not overwrite the requested output until compilation succeeds.
tmp_output="${output}.tmp.$$"
trap 'rm -f "$tmp_output"' EXIT HUP INT TERM

clang --target="$target" "$@" -o "$tmp_output"

# Termux's driver may inject a Termux-specific RUNPATH.
if command -v patchelf >/dev/null 2>&1; then
    patchelf --remove-rpath "$tmp_output"
else
    echo "error: patchelf is required to remove RPATH/RUNPATH" >&2
    exit 127
fi

if readelf -d "$tmp_output" 2>/dev/null |
    grep -Eq '\((RPATH|RUNPATH)\)'; then
    echo "error: RPATH/RUNPATH remains in $tmp_output" >&2
    exit 1
fi

mv -f "$tmp_output" "$output"
trap - EXIT HUP INT TERM
echo "Built and verified: $output"
