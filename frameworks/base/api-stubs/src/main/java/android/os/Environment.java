package android.os;

import java.io.File;

public final class Environment {
    public static final String DIRECTORY_MUSIC = "Music";
    public static final String DIRECTORY_PODCASTS = "Podcasts";
    public static final String DIRECTORY_RINGTONES = "Ringtones";
    public static final String DIRECTORY_ALARMS = "Alarms";
    public static final String DIRECTORY_NOTIFICATIONS = "Notifications";
    public static final String DIRECTORY_PICTURES = "Pictures";
    public static final String DIRECTORY_MOVIES = "Movies";
    public static final String DIRECTORY_DOWNLOADS = "Download";
    public static final String DIRECTORY_DCIM = "DCIM";
    public static final String DIRECTORY_DOCUMENTS = "Documents";

    public static final String MEDIA_UNKNOWN = "unknown";
    public static final String MEDIA_REMOVED = "removed";
    public static final String MEDIA_UNMOUNTED = "unmounted";
    public static final String MEDIA_CHECKING = "checking";
    public static final String MEDIA_NOFS = "nofs";
    public static final String MEDIA_MOUNTED = "mounted";
    public static final String MEDIA_MOUNTED_READ_ONLY = "mounted_ro";
    public static final String MEDIA_SHARED = "shared";
    public static final String MEDIA_BAD_REMOVAL = "bad_removal";
    public static final String MEDIA_UNMOUNTABLE = "unmountable";

    private Environment() {}

    public static File getDataDirectory() {
        return new File("/data");
    }

    public static File getRootDirectory() {
        return new File("/system");
    }

    public static File getSystemDirectory() {
        return new File("/system");
    }

    public static File getVendorDirectory() {
        return new File("/vendor");
    }

    public static File getOdmDirectory() {
        return new File("/odm");
    }

    public static File getProductDirectory() {
        return new File("/product");
    }

    public static File getDownloadCacheDirectory() {
        return new File("/cache");
    }

    public static File getExternalStorageDirectory() {
        return new File("/sdcard");
    }

    public static File getExternalStoragePublicDirectory(String type) {
        if (type == null || type.contains("..")
                || type.startsWith("/")) {
            throw new IllegalArgumentException("Invalid storage type");
        }
        return new File(getExternalStorageDirectory(), type);
    }

    public static String getExternalStorageState() {
        return MEDIA_UNKNOWN;
    }

    public static String getExternalStorageState(File path) {
        return MEDIA_UNKNOWN;
    }

    public static boolean isExternalStorageEmulated() {
        return false;
    }

    public static boolean isExternalStorageEmulated(File path) {
        return false;
    }

    public static boolean isExternalStorageRemovable() {
        return true;
    }

    public static boolean isExternalStorageRemovable(File path) {
        return true;
    }

    public static boolean isExternalStorageLegacy() {
        return false;
    }

    public static boolean isExternalStorageManager() {
        return false;
    }

    public static File getStorageDirectory() {
        return new File("/storage");
    }

    public static File getExpandDirectory() {
        return new File("/mnt/expand");
    }
}
