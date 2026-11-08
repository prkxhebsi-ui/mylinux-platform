package android.content.pm;

public class ApplicationInfo extends PackageItemInfo {
    public int uid;
    public int targetSdkVersion;
    public int minSdkVersion;
    public int versionCode;
    public String versionName;
    public String sourceDir;
    public String publicSourceDir;
    public String dataDir;
    public String nativeLibraryDir;
    public String processName;
    public String taskAffinity;
    public String permission;
    public boolean debuggable;
    public boolean allowBackup;
    public boolean persistent;
    public boolean hasCode = true;
    public boolean supportsRtl;

    public ApplicationInfo() {
    }

    public boolean isSystemApp() {
        return (flags & FLAG_SYSTEM) != 0;
    }

    public static final int FLAG_SYSTEM = 1;
    public static final int FLAG_DEBUGGABLE = 2;
    public static final int FLAG_HAS_CODE = 4;

    public int flags;
}
