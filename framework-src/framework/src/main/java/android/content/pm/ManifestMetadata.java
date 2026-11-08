package android.content.pm;

public class ManifestMetadata {
    public String name;
    public String value;
    public String resource;
    public String type;
    public boolean required;

    public ManifestMetadata() {
    }

    public ManifestMetadata(String name, String value) {
        this.name = name;
        this.value = value;
    }
}
