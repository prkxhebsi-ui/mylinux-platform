"""MyLinux kernel source collection rules."""

def mylinux_kernel_sources(
        name,
        srcs = [],
        hdrs = [],
        visibility = None):
    native.filegroup(
        name = name,
        srcs = srcs + hdrs,
        visibility = visibility,
    )
