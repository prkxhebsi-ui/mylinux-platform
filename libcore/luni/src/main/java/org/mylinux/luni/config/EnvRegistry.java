package org.mylinux.luni.config;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.regex.Pattern;

public final class EnvRegistry {

    private static final Pattern KEY =
            Pattern.compile("[A-Za-z_][A-Za-z0-9_.-]*");

    private final Map<String, String> variables =
            new LinkedHashMap<>();

    private final Map<String, Long> symbols =
            new LinkedHashMap<>();

    private int envFiles;
    private int envsFiles;

    public void loadTree(File root) throws IOException {
        if (root == null || !root.isDirectory()) {
            throw new IOException("Invalid environment root");
        }

        scan(root);
    }

    private void scan(File directory) throws IOException {
        File[] entries = directory.listFiles();

        if (entries == null) {
            throw new IOException(
                    "Cannot read directory: " + directory);
        }

        for (File entry : entries) {
            if (entry.isDirectory()) {
                if (entry.getName().equals(".git") ||
                    entry.getName().equals("out") ||
                    entry.getName().equals("prebuilts")) {
                    continue;
                }

                scan(entry);
            } else if (entry.isFile()) {
                String name = entry.getName();

                if (name.endsWith(".env")) {
                    parseEnv(entry);
                    envFiles++;
                } else if (name.endsWith(".envs")) {
                    parseEnvs(entry);
                    envsFiles++;
                }
            }
        }
    }

    private void parseEnv(File file) throws IOException {
        try (BufferedReader reader =
                new BufferedReader(new FileReader(file))) {

            String line;
            int lineNumber = 0;

            while ((line = reader.readLine()) != null) {
                lineNumber++;
                line = line.trim();

                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }

                if (line.startsWith("export ")) {
                    line = line.substring(7).trim();
                }

                int separator = line.indexOf('=');

                if (separator <= 0) {
                    throw new IOException(
                            "Invalid .env entry: " + file
                            + ":" + lineNumber);
                }

                String key = line.substring(0, separator).trim();
                String value = line.substring(separator + 1).trim();

                if (!KEY.matcher(key).matches()) {
                    throw new IOException(
                            "Invalid .env key: " + file
                            + ":" + lineNumber);
                }

                value = unquote(value);

                if (variables.containsKey(key)) {
                    throw new IOException(
                            "Duplicate environment key: " + key);
                }

                variables.put(key, value);

                System.setProperty("mylinux.env." + key, value);
            }
        }
    }

    private void parseEnvs(File file) throws IOException {
        try (BufferedReader reader =
                new BufferedReader(new FileReader(file))) {

            String line;
            int lineNumber = 0;

            while ((line = reader.readLine()) != null) {
                lineNumber++;
                line = line.trim();

                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }

                String[] fields = line.split("\\s+");

                if (fields.length != 3) {
                    throw new IOException(
                            "Invalid .envs entry: " + file
                            + ":" + lineNumber);
                }

                long value;

                try {
                    value = Long.decode(fields[0]);
                } catch (NumberFormatException exception) {
                    throw new IOException(
                            "Invalid symbol value: " + file
                            + ":" + lineNumber, exception);
                }

                String symbolName = fields[1];
                String symbolType = fields[2];

                if (!KEY.matcher(symbolName).matches() ||
                    !KEY.matcher(symbolType).matches()) {
                    throw new IOException(
                            "Invalid symbol name or type: " + file
                            + ":" + lineNumber);
                }

                if (symbols.containsKey(symbolName)) {
                    throw new IOException(
                            "Duplicate symbol: " + symbolName);
                }

                symbols.put(symbolName, value);

                System.setProperty(
                        "mylinux.symbol." + symbolName,
                        fields[0]);

                System.setProperty(
                        "mylinux.symbol.type." + symbolName,
                        symbolType);
            }
        }
    }

    private String unquote(String value) {
        if (value.length() >= 2) {
            char first = value.charAt(0);
            char last = value.charAt(value.length() - 1);

            if ((first == '"' && last == '"') ||
                (first == '\'' && last == '\'')) {
                return value.substring(1, value.length() - 1);
            }
        }

        return value;
    }

    public String getVariable(String key) {
        return variables.get(key);
    }

    public Long getSymbol(String name) {
        return symbols.get(name);
    }

    public int getEnvFileCount() {
        return envFiles;
    }

    public int getEnvsFileCount() {
        return envsFiles;
    }

    public int getVariableCount() {
        return variables.size();
    }

    public int getSymbolCount() {
        return symbols.size();
    }
}
