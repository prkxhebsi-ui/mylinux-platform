package android.content.pm;

public final class ManifestValidationResult {
    private ManifestDiagnostic[] items = new ManifestDiagnostic[16];
    private int count;

    public void add(ManifestDiagnostic diagnostic) {
        if (diagnostic == null) return;

        if (count == items.length) {
            ManifestDiagnostic[] expanded =
                    new ManifestDiagnostic[items.length * 2];

            for (int i = 0; i < count; i++) expanded[i] = items[i];
            items = expanded;
        }

        items[count++] = diagnostic;
    }

    public int size() {
        return count;
    }

    public ManifestDiagnostic get(int index) {
        if (index < 0 || index >= count) {
            throw new IndexOutOfBoundsException();
        }
        return items[index];
    }

    public ManifestDiagnostic[] toArray() {
        ManifestDiagnostic[] result = new ManifestDiagnostic[count];

        for (int i = 0; i < count; i++) result[i] = items[i];

        return result;
    }

    public boolean hasErrors() {
        for (int i = 0; i < count; i++) {
            ManifestDiagnostic.Severity severity = items[i].severity;

            if (severity == ManifestDiagnostic.Severity.ERROR
                    || severity == ManifestDiagnostic.Severity.FATAL) {
                return true;
            }
        }
        return false;
    }

    public boolean isValid() {
        return !hasErrors();
    }
}
