package android.content.pm;

public class PermissionInfo extends PackageItemInfo {
    public String group;
    public String protectionLevel;
    public String permissionFlags;
    public int requestRes;
    public int descriptionRes;

    public static final int PROTECTION_NORMAL = 0;
    public static final int PROTECTION_DANGEROUS = 1;
    public static final int PROTECTION_SIGNATURE = 2;
    public static final int PROTECTION_INTERNAL = 3;
}
