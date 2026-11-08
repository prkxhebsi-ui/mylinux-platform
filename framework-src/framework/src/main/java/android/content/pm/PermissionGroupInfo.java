package android.content.pm;

public class PermissionGroupInfo extends PackageItemInfo {
    public String description;
    public int requestRes;
    public int priority;
    public boolean visible = true;

    public PermissionGroupInfo() {
    }
}
