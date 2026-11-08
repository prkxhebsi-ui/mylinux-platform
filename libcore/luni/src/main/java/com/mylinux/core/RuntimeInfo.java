package com.mylinux.core;

/** Reports information exposed by the running Java virtual machine. */
public final class RuntimeInfo {
    private RuntimeInfo() {
    }

    public static String javaVersion() {
        return System.getProperty("java.version", "unknown");
    }

    public static String vmName() {
        return System.getProperty("java.vm.name", "unknown");
    }

    public static String vmVendor() {
        return System.getProperty("java.vm.vendor", "unknown");
    }

    public static String osName() {
        return System.getProperty("os.name", "unknown");
    }

    public static String osArchitecture() {
        return System.getProperty("os.arch", "unknown");
    }

    public static int availableProcessors() {
        return Runtime.getRuntime().availableProcessors();
    }

    public static long maximumMemory() {
        return Runtime.getRuntime().maxMemory();
    }

    public static long totalMemory() {
        return Runtime.getRuntime().totalMemory();
    }

    public static long freeMemory() {
        return Runtime.getRuntime().freeMemory();
    }
}
