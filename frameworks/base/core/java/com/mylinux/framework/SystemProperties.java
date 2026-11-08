package com.mylinux.framework;

/**
 * Minimal system-property access interface.
 *
 * A native or Android-specific backend can be connected later.
 */
public final class SystemProperties {
    private SystemProperties() {}

    public static String get(String key) {
        return get(key, "");
    }

    public static String get(String key, String fallback) {
        if (key == null || key.isEmpty()) {
            throw new IllegalArgumentException("Property key is empty");
        }

        try {
            return System.getProperty(key, fallback);
        } catch (SecurityException exception) {
            return fallback;
        }
    }

    public static boolean getBoolean(String key, boolean fallback) {
        String value = get(key, null);

        if (value == null || value.isEmpty()) {
            return fallback;
        }

        return value.equalsIgnoreCase("true")
            || value.equals("1")
            || value.equalsIgnoreCase("yes");
    }
}
