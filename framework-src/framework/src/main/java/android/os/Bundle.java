package android.os;

public class Bundle implements Parcelable, Cloneable {
    private String[] keys;
    private Object[] values;
    private int size;

    public Bundle() {
        keys = new String[8];
        values = new Object[8];
        size = 0;
    }

    public Bundle(int capacity) {
        int actual = capacity < 1 ? 1 : capacity;
        keys = new String[actual];
        values = new Object[actual];
        size = 0;
    }

    public Bundle(Bundle source) {
        this(source == null ? 8 : source.size);
        if (source != null) {
            for (int i = 0; i < source.size; i++) {
                put(source.keys[i], source.values[i]);
            }
        }
    }

    private int indexOf(String key) {
        if (key == null) return -1;
        for (int i = 0; i < size; i++) {
            if (key.equals(keys[i])) return i;
        }
        return -1;
    }

    private void ensureCapacity(int capacity) {
        if (capacity <= keys.length) return;

        int next = keys.length * 2;
        if (next < capacity) next = capacity;

        String[] newKeys = new String[next];
        Object[] newValues = new Object[next];

        for (int i = 0; i < size; i++) {
            newKeys[i] = keys[i];
            newValues[i] = values[i];
        }

        keys = newKeys;
        values = newValues;
    }

    private void put(String key, Object value) {
        if (key == null) throw new IllegalArgumentException("Null key");

        int index = indexOf(key);
        if (index >= 0) {
            values[index] = value;
            return;
        }

        ensureCapacity(size + 1);
        keys[size] = key;
        values[size] = value;
        size++;
    }

    public void putString(String key, String value) {
        put(key, value);
    }

    public String getString(String key) {
        Object value = get(key);
        return value instanceof String ? (String) value : null;
    }

    public String getString(String key, String fallback) {
        String value = getString(key);
        return value == null ? fallback : value;
    }

    public void putInt(String key, int value) {
        put(key, Integer.valueOf(value));
    }

    public int getInt(String key) {
        return getInt(key, 0);
    }

    public int getInt(String key, int fallback) {
        Object value = get(key);
        return value instanceof Integer ? ((Integer) value).intValue() : fallback;
    }

    public void putLong(String key, long value) {
        put(key, Long.valueOf(value));
    }

    public long getLong(String key) {
        return getLong(key, 0L);
    }

    public long getLong(String key, long fallback) {
        Object value = get(key);
        return value instanceof Long ? ((Long) value).longValue() : fallback;
    }

    public void putBoolean(String key, boolean value) {
        put(key, Boolean.valueOf(value));
    }

    public boolean getBoolean(String key) {
        return getBoolean(key, false);
    }

    public boolean getBoolean(String key, boolean fallback) {
        Object value = get(key);
        return value instanceof Boolean
                ? ((Boolean) value).booleanValue() : fallback;
    }

    public void putParcelable(String key, Parcelable value) {
        put(key, value);
    }

    public Parcelable getParcelable(String key) {
        Object value = get(key);
        return value instanceof Parcelable ? (Parcelable) value : null;
    }

    public Object get(String key) {
        int index = indexOf(key);
        return index < 0 ? null : values[index];
    }

    public boolean containsKey(String key) {
        return indexOf(key) >= 0;
    }

    public void remove(String key) {
        int index = indexOf(key);
        if (index < 0) return;

        for (int i = index; i < size - 1; i++) {
            keys[i] = keys[i + 1];
            values[i] = values[i + 1];
        }

        size--;
        keys[size] = null;
        values[size] = null;
    }

    public void clear() {
        for (int i = 0; i < size; i++) {
            keys[i] = null;
            values[i] = null;
        }
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public Bundle clone() {
        return new Bundle(this);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel destination, int flags) {
        destination.writeInt(size);

        for (int i = 0; i < size; i++) {
            destination.writeString(keys[i]);

            Object value = values[i];

            if (value instanceof String) {
                destination.writeInt(1);
                destination.writeString((String) value);
            } else if (value instanceof Integer) {
                destination.writeInt(2);
                destination.writeInt(((Integer) value).intValue());
            } else if (value instanceof Long) {
                destination.writeInt(3);
                destination.writeLong(((Long) value).longValue());
            } else if (value instanceof Boolean) {
                destination.writeInt(4);
                destination.writeInt(((Boolean) value).booleanValue() ? 1 : 0);
            } else if (value == null) {
                destination.writeInt(0);
            } else {
                throw new IllegalStateException(
                        "Unsupported Bundle value: " + value.getClass().getName());
            }
        }
    }
}
