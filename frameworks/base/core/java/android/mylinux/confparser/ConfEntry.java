package android.mylinux.confparser;

public final class ConfEntry {
    private final String section;
    private final String key;
    private final String value;

    public ConfEntry(String section, String key, String value) {
        if (key == null || key.isEmpty()) {
            throw new IllegalArgumentException("Empty configuration key");
        }

        this.section = section == null ? "" : section;
        this.key = key;
        this.value = value == null ? "" : value;
    }

    public String getSection() {
        return section;
    }

    public String getKey() {
        return key;
    }

    public String getValue() {
        return value;
    }

    public String getQualifiedKey() {
        return section.isEmpty() ? key : section + "." + key;
    }
}
