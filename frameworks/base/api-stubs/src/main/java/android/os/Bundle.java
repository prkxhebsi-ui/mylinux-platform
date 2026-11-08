package android.os;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class Bundle {
    private final HashMap<String, Object> values;

    public Bundle() {
        values = new HashMap<>();
    }

    public Bundle(Bundle source) {
        values = new HashMap<>();
        if (source != null) {
            values.putAll(source.values);
        }
    }

    public void putString(String key, String value) {
        values.put(key, value);
    }

    public String getString(String key) {
        Object value = values.get(key);
        return value instanceof String ? (String) value : null;
    }

    public String getString(String key, String fallback) {
        String value = getString(key);
        return value != null ? value : fallback;
    }

    public void putInt(String key, int value) {
        values.put(key, value);
    }

    public int getInt(String key) {
        return getInt(key, 0);
    }

    public int getInt(String key, int fallback) {
        Object value = values.get(key);
        return value instanceof Integer ? (Integer) value : fallback;
    }

    public void putLong(String key, long value) {
        values.put(key, value);
    }

    public long getLong(String key) {
        return getLong(key, 0L);
    }

    public long getLong(String key, long fallback) {
        Object value = values.get(key);
        return value instanceof Long ? (Long) value : fallback;
    }

    public void putBoolean(String key, boolean value) {
        values.put(key, value);
    }

    public boolean getBoolean(String key) {
        return getBoolean(key, false);
    }

    public boolean getBoolean(String key, boolean fallback) {
        Object value = values.get(key);
        return value instanceof Boolean ? (Boolean) value : fallback;
    }

    public void putFloat(String key, float value) {
        values.put(key, value);
    }

    public float getFloat(String key, float fallback) {
        Object value = values.get(key);
        return value instanceof Float ? (Float) value : fallback;
    }

    public void putDouble(String key, double value) {
        values.put(key, value);
    }

    public double getDouble(String key, double fallback) {
        Object value = values.get(key);
        return value instanceof Double ? (Double) value : fallback;
    }

    public void putBundle(String key, Bundle value) {
        values.put(key, value);
    }

    public Bundle getBundle(String key) {
        Object value = values.get(key);
        return value instanceof Bundle ? (Bundle) value : null;
    }

    public void putStringArray(String key, String[] value) {
        values.put(key, value);
    }

    public String[] getStringArray(String key) {
        Object value = values.get(key);
        return value instanceof String[] ? (String[]) value : null;
    }

    public void putIntArray(String key, int[] value) {
        values.put(key, value);
    }

    public int[] getIntArray(String key) {
        Object value = values.get(key);
        return value instanceof int[] ? (int[]) value : null;
    }

    public void putAll(Bundle source) {
        if (source != null) {
            values.putAll(source.values);
        }
    }

    public boolean containsKey(String key) {
        return values.containsKey(key);
    }

    public Object get(String key) {
        return values.get(key);
    }

    public void put(String key, Object value) {
        values.put(key, value);
    }

    public void remove(String key) {
        values.remove(key);
    }

    public void clear() {
        values.clear();
    }

    public int size() {
        return values.size();
    }

    public boolean isEmpty() {
        return values.isEmpty();
    }

    public Set<String> keySet() {
        return values.keySet();
    }

    public Map<String, Object> asMap() {
        return new HashMap<>(values);
    }
}
