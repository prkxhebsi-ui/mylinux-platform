package android.content.pm;

public class PackageInfo {
    public String packageName;
    public String versionName;
    public int versionCode;
    public int targetSdkVersion;
    public int minSdkVersion;

    public ApplicationInfo applicationInfo;
    public ActivityInfo[] activities;
    public ActivityInfo[] receivers;
    public ServiceInfo[] services;
    public ProviderInfo[] providers;
    public PermissionInfo[] permissions;
    public String[] requestedPermissions;
    public FeatureInfo[] features;

    public long firstInstallTime;
    public long lastUpdateTime;
}
