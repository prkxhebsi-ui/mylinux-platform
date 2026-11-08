"""MyLinux Android native build rules."""

load("//build/bazel/rules/cc:defs.bzl", "mylinux_cc_binary", "mylinux_cc_library")

def mylinux_android_library(
        name,
        srcs = [],
        hdrs = [],
        deps = [],
        copts = []):
    mylinux_cc_library(
        name = name,
        srcs = srcs,
        hdrs = hdrs,
        deps = deps,
        copts = copts + ["-D__ANDROID__"],
    )

def mylinux_android_binary(
        name,
        srcs = [],
        deps = [],
        copts = [],
        linkopts = []):
    mylinux_cc_binary(
        name = name,
        srcs = srcs,
        deps = deps,
        copts = copts + ["-D__ANDROID__"],
        linkopts = linkopts,
    )
