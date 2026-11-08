package android.content.pm;

public final class ManifestDiagnostic {
    public enum Severity {
        INFO,
        WARNING,
        ERROR,
        FATAL
    }

    public Severity severity;
    public String code;
    public String message;
    public String element;
    public String attribute;
    public int position;

    public ManifestDiagnostic(
            Severity severity,
            String code,
            String message,
            String element) {
        this.severity = severity;
        this.code = code;
        this.message = message;
        this.element = element;
    }
}
