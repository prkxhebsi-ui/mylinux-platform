package android.content.pm;

public class ProviderInfo extends ComponentInfo {
    public String authority;
    public String readPermission;
    public String writePermission;
    public String[] grantUriPermissions;
    public boolean grantUriPermissionsEnabled;
    public boolean multiprocess;
    public boolean syncable;
    public int initOrder;
}
