#!/data/data/com.termux/files/usr/bin/bash

# MyLinux platform build environment

function gettop() {
    local dir="$PWD"

    while [ "$dir" != "/" ]; do
        if [ -f "$dir/envsetup.sh" ] && [ -d "$dir/device" ] && [ -d "$dir/toolchain" ]; then
            echo "$dir"
            return 0
        fi
        dir="$(dirname "$dir")"
    done

    echo "ERROR: MyLinux platform root not found." >&2
    return 1
}

function mylinux_setup() {
    export TOP
    TOP="$(gettop)" || return 1

    export MYLINUX_TOP="$TOP"
    export MYLINUX_DEVICE="$TOP/device"
    export MYLINUX_TOOLCHAIN="$TOP/toolchain"

    # Go source workspace
    export GOPATH="$TOP/toolchain/go"
    export GOBIN="$GOPATH/bin"
    export GOOS=android
    export GOARCH=arm64

    # Termux host architecture
    export GOHOSTOS=android
    export GOHOSTARCH=arm64

    # Preserve the real installed Go distribution.
    if command -v go >/dev/null 2>&1; then
        export GOROOT="$(go env GOROOT)"
    else
        echo "WARNING: Go compiler not found."
    fi

    export MYLINUX_GO_SOURCE="$GOPATH/src"
    export MYLINUX_BUILD_VARIANT=userdebug

    export MYLINUX_CUTTLEFISH="$TOP/device/google/cuttlefish"

    export PATH="$GOBIN:$PATH"

    echo "======================================"
    echo "       MyLinux Build Environment"
    echo "======================================"
    echo "Platform: $TOP"
    echo "Go source workspace: $GOPATH"
    echo "GOROOT: ${GOROOT:-not installed}"
    echo "GOOS: $GOOS"
    echo "GOARCH: $GOARCH"
    echo "GOHOSTOS: $GOHOSTOS"
    echo "GOHOSTARCH: $GOHOSTARCH"
    echo "======================================"
}

function mylinux_products() {
    local found=0

    echo "Available MyLinux products:"
    echo

    while IFS= read -r file; do
        grep -hE '^[[:space:]]*PRODUCT_NAME[[:space:]]*[:?+]?=' "$file" 2>/dev/null |
        sed -E 's/^[[:space:]]*PRODUCT_NAME[[:space:]]*[:?+]?=[[:space:]]*//' |
        sed 's/[[:space:]#].*$//' |
        while IFS= read -r product; do
            [ -n "$product" ] && echo "  $product"
        done

        found=1
    done < <(find "$TOP/device" -type f -name '*.mk' 2>/dev/null)

    echo
    echo "Product names are read from PRODUCT_NAME assignments."
}

function mylinux_lunch_choices() {
    local file

    find "$TOP/device" -type f -name '*.mk' 2>/dev/null |
    while IFS= read -r file; do
        awk '
        /^[[:space:]]*PRODUCT_NAME[[:space:]]*[:?+]?=/ {
            sub(/^[^=]*=[[:space:]]*/, "")
            sub(/[[:space:]#].*$/, "")
            if ($0 != "") {
                print $0 "-userdebug"
                print $0 "-eng"
                print $0 "-user"
            }
        }

        /^[[:space:]]*COMMON_LUNCH_CHOICES[[:space:]]*[:?+]?=/ {
            sub(/^[^=]*=[[:space:]]*/, "")
            gsub(/\\/, "")
            for (i = 1; i <= NF; i++) {
                if ($i ~ /^[A-Za-z0-9_.-]+$/)
                    print $i
            }
        }
        ' "$file"
    done | sort -u
}

function lunch() {
    local choice="$1"
    local selected=""
    local choices=()
    local index=1

    mapfile -t choices < <(mylinux_lunch_choices)

    if [ "${#choices[@]}" -eq 0 ]; then
        echo "No products found in device/*.mk files."
        return 1
    fi

    if [ -z "$choice" ]; then
        echo
        echo "MyLinux lunch menu"
        echo "------------------"

        for item in "${choices[@]}"; do
            printf " %2d. %s\n" "$index" "$item"
            ((index++))
        done

        echo
        read -r -p "Select product number or name: " choice
    fi

    if [[ "$choice" =~ ^[0-9]+$ ]]; then
        if [ "$choice" -lt 1 ] || [ "$choice" -gt "${#choices[@]}" ]; then
            echo "Invalid selection."
            return 1
        fi
        selected="${choices[$((choice - 1))]}"
    else
        for item in "${choices[@]}"; do
            if [ "$item" = "$choice" ]; then
                selected="$item"
                break
            fi
        done
    fi

    if [ -z "$selected" ]; then
        echo "Unknown product: $choice"
        echo "Run lunch to see available choices."
        return 1
    fi

    export TARGET_PRODUCT="${selected%-userdebug}"
    export TARGET_BUILD_VARIANT="${selected##*-}"
    export TARGET_BUILD_TYPE="$TARGET_BUILD_VARIANT"
    export MYLINUX_TARGET="$selected"

    echo
    echo "Selected MyLinux product:"
    echo "  TARGET_PRODUCT=$TARGET_PRODUCT"
    echo "  TARGET_BUILD_VARIANT=$TARGET_BUILD_VARIANT"
    echo "  MYLINUX_TARGET=$MYLINUX_TARGET"
    echo
}

# Main build command
function m() {
    local top
    top="$(gettop)" || return 1

    if ! command -v make >/dev/null 2>&1; then
        echo "GNU Make is missing. Install it with: pkg install make"
        return 1
    fi

    make -C "$top" "$@"
}

# Build from the current directory
function mm() {
    if [ ! -f "$PWD/Makefile" ] && [ ! -f "$PWD/makefile" ]; then
        echo "No local Makefile in $PWD"
        echo "This directory is not yet an independent build module."
        return 1
    fi

    make -C "$PWD" "$@"
}

# Build one or more module directories
function mmm() {
    if [ "$#" -eq 0 ]; then
        echo "Usage: mmm DIRECTORY [MAKE_TARGET]"
        return 1
    fi

    local dir="$1"
    shift

    if [[ "$dir" != /* ]]; then
        dir="$PWD/$dir"
    fi

    dir="$(realpath -m "$dir")"

    if [ ! -f "$dir/Makefile" ] && [ ! -f "$dir/makefile" ]; then
        echo "No Makefile found in $dir"
        return 1
    fi

    make -C "$dir" "$@"
}

# Build multiple module directories
function mmma() {
    if [ "$#" -eq 0 ]; then
        echo "Usage: mmma DIRECTORY DIRECTORY ..."
        return 1
    fi

    local dir
    local failed=0

    for dir in "$@"; do
        echo
        echo "=== Building $dir ==="

        if ! mmm "$dir"; then
            failed=1
        fi
    done

    return "$failed"
}

function croot() {
    cd "$(gettop)"
}

function cdevice() {
    cd "$(gettop)/device"
}

function ccut() {
    cd "$(gettop)/device/google/cuttlefish"
}

function mylinux_envcheck() {
    echo "MyLinux environment check"
    echo "-------------------------"

    echo "Platform: $TOP"
    echo "Go: $(command -v go || echo missing)"
    echo "Make: $(command -v make || echo missing)"
    echo "Python: $(command -v python || echo missing)"

    if command -v go >/dev/null 2>&1; then
        go version
        go env GOROOT GOPATH GOOS GOARCH GOHOSTOS GOHOSTARCH
    fi
}

mylinux_setup
