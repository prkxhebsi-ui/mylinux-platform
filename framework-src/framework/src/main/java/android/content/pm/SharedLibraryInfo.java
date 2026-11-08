package android.content.pm;

public class SharedLibraryInfo {
    public String name;
    public String packageName;
    public String version;
    public String path;
    public int type;
    public boolean required;

    public static final int TYPE_BUILTIN = 0;
    public static final int TYPE_DYNAMIC = 1;
    public static final int TYPE_STATIC = 2;

    public SharedLibraryInfo() {
    }

    public SharedLibraryInfo(String name, String version) {
        this.name = name;
        this.version = version;
    }
}
