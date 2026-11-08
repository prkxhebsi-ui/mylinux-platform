package com.mylinux.dalvik;

/** Metadata for the MyLinux Dalvik compatibility layer. */
public final class DalvikCompatibility {
    public static final int SCHEMA_VERSION = 1;
    public static final int ANDROID_API_LEVEL = 30;
    public static final boolean DELEGATES_EXECUTION_TO_ART = true;

    private DalvikCompatibility() {}

    public static String runtimeMode() {
        return DELEGATES_EXECUTION_TO_ART
                ? "ART-delegated compatibility"
                : "standalone runtime";
    }

    public static boolean supportsApiLevel(int apiLevel) {
        return apiLevel == ANDROID_API_LEVEL;
    }
}
