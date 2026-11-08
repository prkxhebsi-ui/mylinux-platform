package com.mylinux.core;

import java.util.Objects;

/**
 * Typed access to Java system properties.
 *
 * This is a MyLinux utility, not Android's hidden SystemProperties API.
 */
public final class SystemProperties {
    private SystemProperties() {
    }

    public static String get(String key, String fallback) {
        Objects.requireNonNull(key, "key");
        return System.getProperty(key, fallback);
    }

    public static String get(String key) {
        return get(key, "");
    }

    public static int getInt(String key, int fallback) {
        String value = get(key, null);
        if (value == null) {
            return fallback;
        }

        try {
            return Integer.parseInt(value.trim());
        } catch (NumberFormatException ignored) {
            return fallback;
        }
    }

    public static long getLong(String key, long fallback) {
        String value = get(key, null);
        if (value == null) {
            return fallback;
        }

        try {
            return Long.parseLong(value.trim());
        } catch (NumberFormatException ignored) {
            return fallback;
        }
    }

    public static boolean getBoolean(String key, boolean fallback) {
        String value = get(key, null);
        if (value == null) {
            return fallback;
        }

        switch (value.trim().toLowerCase(java.util.Locale.ROOT)) {
            case "1":
            case "true":
            case "yes":
            case "on":
                return true;
            case "0":
            case "false":
            case "no":
            case "off":
                return false;
            default:
                return fallback;
        }
    }

    public static void set(String key, String value) {
        Objects.requireNonNull(key, "key");
        Objects.requireNonNull(value, "value");
        System.setProperty(key, value);
    }

    public static boolean clear(String key) {
        Objects.requireNonNull(key, "key");
        return System.clearProperty(key) != null;
    }
}
