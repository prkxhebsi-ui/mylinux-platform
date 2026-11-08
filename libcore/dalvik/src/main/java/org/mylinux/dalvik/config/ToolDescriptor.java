package org.mylinux.dalvik.config;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public final class ToolDescriptor {

    private final Properties properties;

    private ToolDescriptor(Properties properties) {
        this.properties = properties;
    }

    public static ToolDescriptor load(File file) throws IOException {
        Properties properties = new Properties();

        try (FileInputStream input = new FileInputStream(file)) {
            properties.load(input);
        }

        String id = properties.getProperty("id");
        String executable = properties.getProperty("executable");

        if (id == null || id.trim().isEmpty()) {
            throw new IOException("Tool descriptor has no ID");
        }

        if (executable == null || executable.trim().isEmpty()) {
            throw new IOException("Tool descriptor has no executable");
        }

        return new ToolDescriptor(properties);
    }

    public String getId() {
        return properties.getProperty("id");
    }

    public String getName() {
        return properties.getProperty("name");
    }

    public String getVersion() {
        return properties.getProperty("version");
    }

    public String getExecutable() {
        return properties.getProperty("executable");
    }

    public String getType() {
        return properties.getProperty("type", "unknown");
    }

    public boolean isEnabled() {
        return Boolean.parseBoolean(
                properties.getProperty("enabled", "false")
        );
    }

    public String getDescription() {
        return properties.getProperty("description", "");
    }
}
