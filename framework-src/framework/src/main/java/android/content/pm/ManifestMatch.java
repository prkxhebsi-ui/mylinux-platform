package android.content.pm;

public class ManifestMatch {
    public boolean matched;
    public int score;
    public String packageName;
    public String componentName;
    public String reason;

    public ManifestMatch() {
        matched = false;
        score = 0;
        packageName = "";
        componentName = "";
        reason = "";
    }

    public void accept(String packageValue, String componentValue) {
        matched = true;
        score++;
        packageName = packageValue;
        componentName = componentValue;
        reason = "MATCH";
    }

    public void reject(String message) {
        matched = false;
        score = 0;
        reason = message;
    }

    public boolean isMatch() {
        return matched;
    }
}
