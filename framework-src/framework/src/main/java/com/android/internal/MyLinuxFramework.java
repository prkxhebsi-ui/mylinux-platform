package com.android.internal;

/**
 * MyLinux framework development interface.
 *
 * This is a prototype, not an Android SDK replacement.
 */
public final class MyLinuxFramework {

    public static final String NAME = "MyLinux Framework";
    public static final int VERSION = 1;

    private MyLinuxFramework() {
        // Utility class.
    }

    public static String getName() {
        return NAME;
    }

    public static int getVersion() {
        return VERSION;
    }
}
