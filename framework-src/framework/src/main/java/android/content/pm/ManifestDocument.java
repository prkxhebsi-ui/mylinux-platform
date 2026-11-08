package android.content.pm;

public final class ManifestDocument {
    public ManifestNode root;
    public String packageName;
    public String sourceName;
    public String namespace;
    public long revision;
    public boolean parsed;
    public boolean validated;
    public ManifestGeneration generation = ManifestGeneration.PRESENT;

    public ManifestDocument(ManifestNode root) {
        this.root = root;
        refreshMetadata();
    }

    public void refreshMetadata() {
        if (root == null) return;

        packageName = root.getAttribute("package");
        namespace = root.getAttribute("xmlns:android");
    }

    public ManifestNode getApplication() {
        return root == null ? null : root.getChild("application");
    }

    public ManifestNode[] getComponents() {
        ManifestNode application = getApplication();

        if (application == null) return new ManifestNode[0];

        int count = 0;

        for (int i = 0; i < application.childCount; i++) {
            if (isComponent(application.children[i].name)) count++;
        }

        ManifestNode[] result = new ManifestNode[count];
        int position = 0;

        for (int i = 0; i < application.childCount; i++) {
            ManifestNode child = application.children[i];
            if (isComponent(child.name)) result[position++] = child;
        }

        return result;
    }

    private boolean isComponent(String name) {
        return "activity".equals(name)
                || "activity-alias".equals(name)
                || "service".equals(name)
                || "receiver".equals(name)
                || "provider".equals(name);
    }

    public ManifestDocument copy() {
        ManifestDocument result = new ManifestDocument(
                root == null ? null : root.deepCopy());

        result.sourceName = sourceName;
        result.revision = revision;
        result.generation = generation;
        result.parsed = parsed;
        result.validated = validated;

        return result;
    }
}
