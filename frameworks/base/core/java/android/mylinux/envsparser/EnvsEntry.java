package android.mylinux.envsparser;

public final class EnvsEntry {
    private final long value;
    private final String symbol;
    private final String type;

    public EnvsEntry(long value, String symbol, String type) {
        if (symbol == null || symbol.isEmpty()
                || type == null || type.isEmpty()) {
            throw new IllegalArgumentException(
                "Invalid environment symbol");
        }

        this.value = value;
        this.symbol = symbol;
        this.type = type;
    }

    public long getValue() {
        return value;
    }

    public String getSymbol() {
        return symbol;
    }

    public String getType() {
        return type;
    }
}
