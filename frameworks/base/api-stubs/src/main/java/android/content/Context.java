package android.content;

import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;

import java.io.File;

public abstract class Context {
    public static final String WIFI_SERVICE = "wifi";
    public static final String TELEPHONY_SERVICE = "phone";
    public static final String CONNECTIVITY_SERVICE = "connectivity";
    public static final String AUDIO_SERVICE = "audio";
    public static final String LOCATION_SERVICE = "location";
    public static final String POWER_SERVICE = "power";
    public static final String NOTIFICATION_SERVICE = "notification";
    public static final String ACTIVITY_SERVICE = "activity";
    public static final String WINDOW_SERVICE = "window";
    public static final String SENSOR_SERVICE = "sensor";
    public static final String STORAGE_SERVICE = "storage";
    public static final String VIBRATOR_SERVICE = "vibrator";
    public static final String INPUT_METHOD_SERVICE = "input_method";

    public static final int MODE_PRIVATE = 0;
    public static final int MODE_WORLD_READABLE = 1;
    public static final int MODE_WORLD_WRITEABLE = 2;
    public static final int MODE_APPEND = 0x8000;

    public abstract Object getSystemService(String name);

    public <T> T getSystemService(Class<T> serviceClass) {
        if (serviceClass == null) return null;
        Object service = getSystemService(
                serviceClass.getName());
        return serviceClass.isInstance(service)
                ? serviceClass.cast(service) : null;
    }

    public abstract String getPackageName();

    public abstract File getFilesDir();

    public abstract File getCacheDir();

    public SharedPreferences getSharedPreferences(
            String name, int mode) {
        throw new UnsupportedOperationException(
                "SharedPreferences not implemented");
    }

    public Context getApplicationContext() {
        return this;
    }

    public ClassLoader getClassLoader() {
        return getClass().getClassLoader();
    }

    public PackageManager getPackageManager() {
        throw new UnsupportedOperationException(
                "PackageManager not implemented");
    }

    public ApplicationInfo getApplicationInfo() {
        throw new UnsupportedOperationException(
                "ApplicationInfo not implemented");
    }

    public File getDataDir() {
        File files = getFilesDir();
        return files == null ? null : files.getParentFile();
    }

    public File getCodeCacheDir() {
        File directory = new File(getCacheDir(), "code_cache");
        if (!directory.exists()) directory.mkdirs();
        return directory;
    }

    public File getNoBackupFilesDir() {
        File directory = new File(getFilesDir(), "no_backup");
        if (!directory.exists()) directory.mkdirs();
        return directory;
    }

    public File getDir(String name, int mode) {
        if (name == null || name.isEmpty()
                || name.contains("/") || name.equals(".")
                || name.equals("..")) {
            throw new IllegalArgumentException("Invalid directory name");
        }

        File directory = new File(getFilesDir(), "app_" + name);
        if (!directory.exists() && !directory.mkdirs()) {
            throw new IllegalStateException(
                    "Cannot create directory: " + directory);
        }
        return directory;
    }

    public File getFileStreamPath(String name) {
        return new File(getFilesDir(), name);
    }

    public File getDatabasePath(String name) {
        File directory = new File(getDataDir(), "databases");
        if (!directory.exists()) directory.mkdirs();
        return new File(directory, name);
    }

    public void startActivity(Intent intent) {
        throw new UnsupportedOperationException(
                "Activity launching not implemented");
    }

    public void startActivity(Intent intent, Object options) {
        startActivity(intent);
    }

    public String getString(int resourceId) {
        throw new UnsupportedOperationException(
                "Resources not implemented");
    }

    public String getPackageResourcePath() {
        throw new UnsupportedOperationException(
                "Package resources not implemented");
    }

    public String getPackageCodePath() {
        throw new UnsupportedOperationException(
                "Package code path not implemented");
    }
}
