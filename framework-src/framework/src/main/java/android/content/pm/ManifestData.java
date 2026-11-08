package android.content.pm;

public class ManifestData {
    public String scheme;
    public String host;
    public String port;
    public String path;
    public String pathPrefix;
    public String pathPattern;
    public String mimeType;
    public String mimeGroup;

    public boolean matchesScheme(String candidate) {
        return scheme == null || scheme.equals(candidate);
    }

    public boolean matchesHost(String candidate) {
        return host == null || host.equals(candidate);
    }

    public boolean matchesMimeType(String candidate) {
        return mimeType == null || mimeType.equals(candidate)
                || "*/*".equals(mimeType);
    }
}
