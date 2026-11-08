#include <mylinux/metadata.h>

MYLINUX_METADATA(platform, "MyLinux", MYLINUX_META_PLATFORM, 1);
MYLINUX_METADATA(library, "libmylinux.so", MYLINUX_META_LIBRARY, 1);
MYLINUX_METADATA(abi, "aarch64-linux-android", MYLINUX_META_PLATFORM, 1);
MYLINUX_METADATA(math, "basic+advanced", MYLINUX_META_FEATURE, 1);
MYLINUX_METADATA(syscalls, "mount,umount2,mmap,munmap,mprotect,brk",
                 MYLINUX_META_SYSCALL, 1);
