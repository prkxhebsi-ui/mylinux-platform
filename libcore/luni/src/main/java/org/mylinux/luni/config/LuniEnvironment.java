package org.mylinux.luni.config;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;

public final class LuniEnvironment {

    public static final long EXPECTED_MAGIC = 0x18383989L;

    public static final class Symbol {
        private final long value;
        private final String name;
        private final String type;

        Symbol(long value, String name, String type) {
            this.value = value;
            this.name = name;
            this.type = type;
        }

        public long getValue() {
            return value;
        }

        public String getName() {
            return name;
        }

        public String getType() {
            return type;
        }
    }

    private final Map<String, Symbol> symbols;

    private LuniEnvironment(Map<String, Symbol> symbols) {
        this.symbols = Collections.unmodifiableMap(
                new LinkedHashMap<>(symbols));
    }

    public static LuniEnvironment load(File file)
            throws IOException {

        Map<String, Symbol> symbols = new LinkedHashMap<>();

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

                String[] columns = line.split("\\s+");

                if (columns.length != 3) {
                    throw new IOException(
                            "Invalid symbol at line " + lineNumber);
                }

                long value;

                try {
                    value = Long.decode(columns[0]);
                } catch (NumberFormatException exception) {
                    throw new IOException(
                            "Invalid hexadecimal value at line "
                                    + lineNumber,
                            exception);
                }

                String name = columns[1];
                String type = columns[2];

                if (!name.matches("[A-Za-z_][A-Za-z0-9_]*")) {
                    throw new IOException(
                            "Invalid symbol name at line "
                                    + lineNumber);
                }

                if (!type.matches("[A-Za-z_][A-Za-z0-9_]*")) {
                    throw new IOException(
                            "Invalid symbol type at line "
                                    + lineNumber);
                }

                if (symbols.containsKey(name)) {
                    throw new IOException(
                            "Duplicate symbol: " + name);
                }

                symbols.put(name,
                        new Symbol(value, name, type));
            }
        }

        LuniEnvironment environment =
                new LuniEnvironment(symbols);

        environment.validate();

        return environment;
    }

    private void validate() throws IOException {
        Symbol magic = symbols.get("ENV_MAGIC");

        if (magic == null) {
            throw new IOException("ENV_MAGIC is missing");
        }

        if (magic.getValue() != EXPECTED_MAGIC) {
            throw new IOException("Incorrect ENV_MAGIC value");
        }

        if (!"mylinux_example".equals(
                getSymbolName("ENV_MAGIC"))) {
            throw new IOException("Unexpected environment identity");
        }

        if (symbols.get("ENV_ARCH") == null) {
            throw new IOException("ENV_ARCH is missing");
        }

        if (symbols.get("ENV_TARGET") == null) {
            throw new IOException("ENV_TARGET is missing");
        }
    }

    public Symbol getSymbol(String name) {
        return symbols.get(name);
    }

    public long getValue(String name, long fallback) {
        Symbol symbol = symbols.get(name);

        return symbol == null ? fallback : symbol.getValue();
    }

    public String getSymbolName(String name) {
        Symbol symbol = symbols.get(name);

        return symbol == null ? null : symbol.getName();
    }

    public String getSymbolType(String name) {
        Symbol symbol = symbols.get(name);

        return symbol == null ? null : symbol.getType();
    }

    public int size() {
        return symbols.size();
    }

    public Map<String, Symbol> getSymbols() {
        return symbols;
    }

    public boolean contains(String name) {
        return symbols.containsKey(name);
    }
}
