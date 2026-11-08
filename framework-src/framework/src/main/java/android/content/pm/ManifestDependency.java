package android.content.pm;

public class ManifestDependency {
    public String packageName;
    public String minimumVersion;
    public String maximumVersion;
    public String libraryName;
    public boolean required = true;
    public boolean optional;

    public boolean acceptsVersion(int version, int minimum, int maximum) {
        if (minimum > 0 && version < minimum) return false;
        if (maximum > 0 && version > maximum) return false;
        return true;
    }
}
