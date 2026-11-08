package android.mylinux.envsparser;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public final class EnvsRegistry {
    private final Map<String, EnvsEntry> symbols =
        new LinkedHashMap<>();

    private final Map<String, EnvsEntry> types =
        new LinkedHashMap<>();

    public synchronized void load(File file) throws IOException {
        try (FileReader reader = new FileReader(file)) {
            List<EnvsEntry> parsed = EnvsParser.parse(reader);

            for (EnvsEntry entry : parsed) {
                if (symbols.containsKey(entry.getSymbol())) {
                    throw new IOException(
                        "Duplicate environment symbol: "
                        + entry.getSymbol());
                }

                if (types.containsKey(entry.getType())) {
                    throw new IOException(
                        "Duplicate environment type: "
                        + entry.getType());
                }

                symbols.put(entry.getSymbol(), entry);
                types.put(entry.getType(), entry);
            }
        }
    }

    public synchronized EnvsEntry getSymbol(String symbol) {
        return symbols.get(symbol);
    }

    public synchronized EnvsEntry getType(String type) {
        return types.get(type);
    }

    public synchronized Map<String, EnvsEntry> getSymbols() {
        return Collections.unmodifiableMap(
            new LinkedHashMap<>(symbols));
    }
}
