package org.mylinux.dalvik.config;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ByteArrayOutputStream;
import java.nio.charset.StandardCharsets;
import java.util.Properties;
import org.json.JSONObject;

public final class RuntimeConfig {

    private final Properties properties;
    private final JSONObject metadata;

    private RuntimeConfig(Properties properties, JSONObject metadata) {
        this.properties = properties;
        this.metadata = metadata;
    }

    public static RuntimeConfig load(
            File configFile,
            File jsonFile
    ) throws IOException {

        Properties properties = new Properties();

        try (InputStream input = new FileInputStream(configFile)) {
            properties.load(input);
        }

        byte[] jsonBytes;

        try (InputStream input = new FileInputStream(jsonFile);
             ByteArrayOutputStream output = new ByteArrayOutputStream()) {

            byte[] buffer = new byte[4096];
            int count;

            while ((count = input.read(buffer)) != -1) {
                output.write(buffer, 0, count);
            }

            jsonBytes = output.toByteArray();
        }

        String jsonText = new String(
                jsonBytes,
                StandardCharsets.UTF_8
        );

        JSONObject metadata = new JSONObject(jsonText);

        return new RuntimeConfig(properties, metadata);
    }

    public String get(String key) {
        return properties.getProperty(key);
    }

    public String get(String key, String fallback) {
        return properties.getProperty(key, fallback);
    }

    public boolean getBoolean(String key, boolean fallback) {
        String value = properties.getProperty(key);

        return value == null
                ? fallback
                : Boolean.parseBoolean(value);
    }

    public int getInt(String key, int fallback) {
        String value = properties.getProperty(key);

        if (value == null) {
            return fallback;
        }

        try {
            return Integer.parseInt(value);
        } catch (NumberFormatException exception) {
            return fallback;
        }
    }

    public JSONObject getMetadata() {
        return metadata;
    }

    public String getRuntimeName() {
        return metadata.optString("name", "Unknown runtime");
    }

    public String getRuntimeVersion() {
        return metadata.optString("version", "Unknown");
    }
}
