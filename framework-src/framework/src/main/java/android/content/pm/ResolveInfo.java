package android.content.pm;

public class ResolveInfo {
    public ActivityInfo activityInfo;
    public ServiceInfo serviceInfo;
    public ProviderInfo providerInfo;
    public String resolvePackageName;
    public String filterLabel;
    public int priority;
    public int preferredOrder;
    public int match;
    public boolean isDefault;
    public boolean system;
    public int specificIndex = -1;

    public PackageItemInfo getComponentInfo() {
        if (activityInfo != null) return activityInfo;
        if (serviceInfo != null) return serviceInfo;
        if (providerInfo != null) return providerInfo;
        return null;
    }

    public String getComponentType() {
        if (activityInfo != null) return "activity";
        if (serviceInfo != null) return "service";
        if (providerInfo != null) return "provider";
        return "unknown";
    }
}
