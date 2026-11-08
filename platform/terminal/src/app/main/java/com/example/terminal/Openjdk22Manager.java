package com.example.terminal;

import java.io.File;

public final class Openjdk22Manager {
    public static final String VERSION = "22";
    public static final String PACKAGE = "openjdk";

    private final File prefix;

    public Openjdk22Manager(File prefix) {
        if (prefix == null) {
            throw new IllegalArgumentException("PREFIX required");
        }
        this.prefix = prefix;
    }

    public File getRuntimeDirectory() {
        return new File(prefix, "lib64/openjdk-22");
    }

    public File getJavaExecutable() {
        return new File(getRuntimeDirectory(), "bin/java");
    }

    public boolean isRegistered() {
        return new File(prefix,
                "var/packages/openjdk/installed").isFile();
    }

    public boolean isRuntimeAvailable() {
        return getJavaExecutable().isFile();
    }

    public String getStatus() {
        if (!isRegistered()) return "OpenJDK 22 is not registered";
        if (!isRuntimeAvailable()) {
            return "OpenJDK 22 manager registered; runtime not installed";
        }
        return "OpenJDK 22 runtime available";
    }
}
