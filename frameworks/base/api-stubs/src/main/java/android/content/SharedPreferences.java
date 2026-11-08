package android.content;

import java.util.Map;

public interface SharedPreferences {

    Map<String, ?> getAll();

    String getString(String key, String defaultValue);

    boolean getBoolean(String key, boolean defaultValue);

    int getInt(String key, int defaultValue);

    long getLong(String key, long defaultValue);

    float getFloat(String key, float defaultValue);

    boolean contains(String key);

    Editor edit();

    void registerOnSharedPreferenceChangeListener(
            OnSharedPreferenceChangeListener listener);

    void unregisterOnSharedPreferenceChangeListener(
            OnSharedPreferenceChangeListener listener);

    interface Editor {
        Editor putString(String key, String value);
        Editor putBoolean(String key, boolean value);
        Editor putInt(String key, int value);
        Editor putLong(String key, long value);
        Editor putFloat(String key, float value);
        Editor remove(String key);
        Editor clear();
        boolean commit();
        void apply();
    }

    interface OnSharedPreferenceChangeListener {
        void onSharedPreferenceChanged(
                SharedPreferences preferences, String key);
    }
}
