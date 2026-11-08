package android.content.pm;

public final class ManifestRegistry {
    private static ManifestRegistry instance;

    private ManifestDocument[] documents = new ManifestDocument[16];
    private int count;
    private long revision;

    private ManifestRegistry() {
    }

    public static synchronized ManifestRegistry getInstance() {
        if (instance == null) instance = new ManifestRegistry();
        return instance;
    }

    public synchronized boolean register(ManifestDocument document) {
        if (document == null || document.root == null) return false;
        if (document.packageName == null) return false;

        int index = findIndex(document.packageName);

        if (index >= 0) {
            document.revision = ++revision;
            documents[index] = document;
            return true;
        }

        if (count == documents.length) {
            ManifestDocument[] expanded =
                    new ManifestDocument[documents.length * 2];

            for (int i = 0; i < count; i++) expanded[i] = documents[i];
            documents = expanded;
        }

        document.revision = ++revision;
        documents[count++] = document;
        return true;
    }

    public synchronized ManifestDocument find(String packageName) {
        int index = findIndex(packageName);
        return index < 0 ? null : documents[index];
    }

    public synchronized boolean unregister(String packageName) {
        int index = findIndex(packageName);
        if (index < 0) return false;

        for (int i = index; i < count - 1; i++) {
            documents[i] = documents[i + 1];
        }

        documents[--count] = null;
        revision++;
        return true;
    }

    public synchronized int size() {
        return count;
    }

    public synchronized long getRevision() {
        return revision;
    }

    public synchronized ManifestDocument[] snapshot() {
        ManifestDocument[] result = new ManifestDocument[count];

        for (int i = 0; i < count; i++) {
            result[i] = documents[i];
        }

        return result;
    }

    private int findIndex(String packageName) {
        if (packageName == null) return -1;

        for (int i = 0; i < count; i++) {
            if (packageName.equals(documents[i].packageName)) return i;
        }

        return -1;
    }
}
