package android.content.pm;

public class ComponentInfo extends PackageItemInfo {
    public ApplicationInfo applicationInfo;
    public String processName;
    public String permission;
    public boolean enabled = true;
    public boolean exported;

    public ComponentInfo() {
    }

    public boolean isEnabled() {
        return enabled &&
            (applicationInfo == null || applicationInfo.enabled);
    }
}
