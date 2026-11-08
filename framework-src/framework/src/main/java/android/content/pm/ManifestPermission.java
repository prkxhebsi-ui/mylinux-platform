package android.content.pm;

public class ManifestPermission {
    public String name;
    public String group;
    public String description;
    public String protectionLevel;
    public String permissionFlags;
    public boolean required = true;
    public boolean runtime;
    public boolean granted;

    public static final int LEVEL_NORMAL = 0;
    public static final int LEVEL_DANGEROUS = 1;
    public static final int LEVEL_SIGNATURE = 2;
    public static final int LEVEL_INTERNAL = 3;
}
