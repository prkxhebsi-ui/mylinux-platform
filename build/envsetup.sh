#!/data/data/com.termux/files/usr/bin/bash

_MYLINUX_ENV_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if [ ! -f "$_MYLINUX_ENV_DIR/envsetup.sh" ]; then
    echo "MyLinux envsetup.sh not found."
    return 1
fi

source "$_MYLINUX_ENV_DIR/envsetup.sh"
unset _MYLINUX_ENV_DIR
