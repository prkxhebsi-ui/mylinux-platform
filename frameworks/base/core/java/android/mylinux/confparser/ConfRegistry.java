package android.mylinux.confparser;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.List;

public final class ConfRegistry {
    private final Map<String, ConfEntry> entries =
        new LinkedHashMap<>();

    public synchronized void load(File file) throws IOException {
        try (FileReader reader = new FileReader(file)) {
            List<ConfEntry> parsed = ConfParser.parse(reader);

            for (ConfEntry entry : parsed) {
                String key = entry.getQualifiedKey();

                if (entries.containsKey(key)) {
                    throw new IOException(
                        "Duplicate configuration: " + key);
                }

                entries.put(key, entry);
            }
        }
    }

    public synchronized String get(String section, String key) {
        String qualified = section == null || section.isEmpty()
            ? key : section + "." + key;

        ConfEntry entry = entries.get(qualified);
        return entry == null ? null : entry.getValue();
    }

    public synchronized Map<String, ConfEntry> getEntries() {
        return Collections.unmodifiableMap(
            new LinkedHashMap<>(entries));
    }
}
