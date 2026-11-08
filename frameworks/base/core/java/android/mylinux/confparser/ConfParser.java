package android.mylinux.confparser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public final class ConfParser {
    private ConfParser() {}

    public static List<ConfEntry> parse(Reader source)
            throws IOException {
        BufferedReader reader = new BufferedReader(source);

        List<ConfEntry> entries = new ArrayList<>();
        Map<String, Boolean> seen = new LinkedHashMap<>();

        String section = "";
        String line;
        int lineNumber = 0;

        while ((line = reader.readLine()) != null) {
            lineNumber++;
            line = line.trim();

            if (line.isEmpty() || line.startsWith("#")
                    || line.startsWith(";")) {
                continue;
            }

            if (line.startsWith("[") && line.endsWith("]")) {
                section = line.substring(1, line.length() - 1).trim();

                if (section.isEmpty()) {
                    throw new IOException(
                        "Empty section at line " + lineNumber);
                }
                continue;
            }

            int separator = line.indexOf('=');

            if (separator <= 0) {
                throw new IOException(
                    "Invalid configuration at line " + lineNumber);
            }

            String key = line.substring(0, separator).trim();
            String value = line.substring(separator + 1).trim();

            if (key.isEmpty()) {
                throw new IOException(
                    "Empty key at line " + lineNumber);
            }

            String qualified = section + "\u0000" + key;

            if (seen.containsKey(qualified)) {
                throw new IOException(
                    "Duplicate key '" + key + "' at line " + lineNumber);
            }

            seen.put(qualified, Boolean.TRUE);
            entries.add(new ConfEntry(section, key, value));
        }

        return Collections.unmodifiableList(entries);
    }
}
