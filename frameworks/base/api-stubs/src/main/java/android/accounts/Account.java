package android.accounts;

public final class Account {
    public final String name;
    public final String type;

    public Account(String name, String type) {
        if (name == null || type == null) {
            throw new IllegalArgumentException("name and type must not be null");
        }
        this.name = name;
        this.type = type;
    }

    @Override
    public String toString() {
        return name + " (" + type + ")";
    }
}
