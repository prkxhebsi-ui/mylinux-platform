package android.content.pm;

public class PackageInfo {
    public String packageName;
    public String versionName;
    public int versionCode;
    public long longVersionCode;

    public long firstInstallTime;
    public long lastUpdateTime;

    public ApplicationInfo applicationInfo;

    public String[] requestedPermissions;
    public int[] requestedPermissionsFlags;

    public static final int INSTALL_LOCATION_AUTO = 0;
    public static final int INSTALL_LOCATION_INTERNAL_ONLY = 1;
    public static final int INSTALL_LOCATION_PREFER_EXTERNAL = 2;

    public long getLongVersionCode() {
        return longVersionCode != 0
                ? longVersionCode : versionCode;
    }
}
