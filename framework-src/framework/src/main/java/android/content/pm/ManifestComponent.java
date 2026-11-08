package android.content.pm;

public class ManifestComponent {
    public String name;
    public String process;
    public String permission;
    public String parentActivity;
    public String targetActivity;
    public String taskAffinity;
    public String exportedState;
    public String enabledState;

    public int type;
    public boolean enabled = true;
    public boolean exported;
    public boolean directBootAware;
    public boolean isolatedProcess;

    public ManifestIntentFilter[] intentFilters;
    public ManifestMetadata[] metadata;

    public static final int TYPE_ACTIVITY = 1;
    public static final int TYPE_SERVICE = 2;
    public static final int TYPE_RECEIVER = 3;
    public static final int TYPE_PROVIDER = 4;
}
