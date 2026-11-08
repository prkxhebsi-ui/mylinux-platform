package android.mylinux.envsparser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public final class EnvsParser {
    private EnvsParser() {}

    public static List<EnvsEntry> parse(Reader source)
            throws IOException {
        BufferedReader reader = new BufferedReader(source);

        List<EnvsEntry> entries = new ArrayList<>();
        Set<String> symbols = new HashSet<>();
        Set<String> types = new HashSet<>();

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
                    "Expected 3 columns at line " + lineNumber);
            }

            long value;

            try {
                value = Long.decode(fields[0]);
            } catch (NumberFormatException error) {
                throw new IOException(
                    "Invalid hexadecimal value at line "
                    + lineNumber, error);
            }

            String symbol = fields[1];
            String type = fields[2];

            if (!symbols.add(symbol)) {
                throw new IOException(
                    "Duplicate symbol '" + symbol
                    + "' at line " + lineNumber);
            }

            if (!types.add(type)) {
                throw new IOException(
                    "Duplicate symbol type '" + type
                    + "' at line " + lineNumber);
            }

            entries.add(new EnvsEntry(value, symbol, type));
        }

        return Collections.unmodifiableList(entries);
    }
}
