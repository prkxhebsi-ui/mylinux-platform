package android.content.pm;

public class PackageItemInfo {
    public String name;
    public String packageName;
    public String label;
    public String description;
    public String icon;
    public String banner;
    public String logo;
    public int labelResource;
    public int iconResource;
    public int descriptionResource;
    public boolean enabled = true;
    public boolean exported;

    public PackageItemInfo() {
    }

    public PackageItemInfo(String packageName, String name) {
        this.packageName = packageName;
        this.name = name;
    }

    public boolean isEnabled() {
        return enabled;
    }

    public void setEnabled(boolean value) {
        enabled = value;
    }

    public String getQualifiedName() {
        if (packageName == null || name == null) return name;
        if (name.startsWith(".")) return packageName + name;
        if (name.indexOf('.') < 0) return packageName + "." + name;
        return name;
    }
}
