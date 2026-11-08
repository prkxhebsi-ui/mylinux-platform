package android.content.pm;

public class ManifestFeature {
    public String name;
    public String version;
    public boolean required = true;
    public int flags;

    public static final int FLAG_REQUIRED = 1;
    public static final int FLAG_OPTIONAL = 2;
}
