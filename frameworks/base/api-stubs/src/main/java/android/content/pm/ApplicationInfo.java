package android.content.pm;

import android.os.Bundle;

public class ApplicationInfo {
    public String packageName;
    public String className;
    public String processName;
    public String taskAffinity;
    public String permission;

    public String sourceDir;
    public String publicSourceDir;
    public String[] splitSourceDirs;
    public String[] splitPublicSourceDirs;
    public String nativeLibraryDir;
    public String dataDir;
    public String deviceProtectedDataDir;

    public int uid;
    public int targetSdkVersion;
    public int minSdkVersion;
    public int maxSdkVersion;

    public int flags;
    public int privateFlags;
    public int theme;
    public int icon;
    public int labelRes;
    public int descriptionRes;

    public boolean enabled = true;
    public boolean isBackupAllowed = true;

    public Bundle metaData;

    public static final int FLAG_SYSTEM = 1;
    public static final int FLAG_DEBUGGABLE = 2;
    public static final int FLAG_HAS_CODE = 4;
    public static final int FLAG_PERSISTENT = 8;
    public static final int FLAG_ALLOW_BACKUP = 0x8000;
    public static final int FLAG_TEST_ONLY = 0x10000;

    public boolean isSystemApp() {
        return (flags & FLAG_SYSTEM) != 0;
    }

    public boolean isDebuggable() {
        return (flags & FLAG_DEBUGGABLE) != 0;
    }

    public boolean hasCode() {
        return (flags & FLAG_HAS_CODE) != 0;
    }
}
