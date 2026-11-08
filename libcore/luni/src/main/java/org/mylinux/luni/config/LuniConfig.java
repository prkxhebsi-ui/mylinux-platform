package org.mylinux.luni.config;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public final class LuniConfig {

    private final Properties properties;

    private LuniConfig(Properties properties) {
        this.properties = properties;
    }

    public static LuniConfig load(File file)
            throws IOException {

        Properties properties = new Properties();

        try (InputStream input = new FileInputStream(file)) {
            properties.load(input);
        }

        return new LuniConfig(properties);
    }

    public String get(String key) {
        return properties.getProperty(key);
    }

    public String get(String key, String fallback) {
        return properties.getProperty(key, fallback);
    }

    public boolean getBoolean(String key, boolean fallback) {
        String value = get(key);

        return value == null
                ? fallback
                : Boolean.parseBoolean(value);
    }

    public int getInt(String key, int fallback) {
        String value = get(key);

        if (value == null) {
            return fallback;
        }

        try {
            return Integer.parseInt(value);
        } catch (NumberFormatException exception) {
            return fallback;
        }
    }

    public String getName() {
        return get("luni.name", "MyLinux Luni");
    }

    public String getVersion() {
        return get("luni.version", "unknown");
    }
}
