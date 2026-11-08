package com.mylinux.framework;

/**
 * Provides basic information about the MyLinux runtime.
 */
public final class SystemRuntime {
    private SystemRuntime() {}

    public static String getName() {
        return "MyLinux";
    }

    public static String getVersion() {
        return System.getProperty("mylinux.version", "unknown");
    }

    public static String getAndroidRelease() {
        return System.getProperty("ro.build.version.release", "unknown");
    }

    public static int getSdkVersion() {
        try {
            return Integer.parseInt(
                System.getProperty("ro.build.version.sdk", "0")
            );
        } catch (NumberFormatException exception) {
            return 0;
        }
    }
}
