"""MyLinux C/C++ build macros."""

def mylinux_cc_library(
        name,
        srcs = [],
        hdrs = [],
        deps = [],
        copts = [],
        visibility = None):
    native.cc_library(
        name = name,
        srcs = srcs,
        hdrs = hdrs,
        deps = deps,
        copts = copts,
        visibility = visibility,
    )

def mylinux_cc_binary(
        name,
        srcs = [],
        deps = [],
        copts = [],
        linkopts = [],
        visibility = None):
    native.cc_binary(
        name = name,
        srcs = srcs,
        deps = deps,
        copts = copts,
        linkopts = linkopts,
        visibility = visibility,
    )

def mylinux_cc_test(
        name,
        srcs = [],
        deps = [],
        copts = [],
        visibility = None):
    native.cc_test(
        name = name,
        srcs = srcs,
        deps = deps,
        copts = copts,
        visibility = visibility,
    )
