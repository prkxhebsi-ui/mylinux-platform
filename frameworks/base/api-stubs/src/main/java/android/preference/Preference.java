package android.preference;

public class Preference {
    private CharSequence title;
    private CharSequence summary;
    private boolean enabled = true;

    public void setTitle(CharSequence title) {
        this.title = title;
    }

    public CharSequence getTitle() {
        return title;
    }

    public void setSummary(CharSequence summary) {
        this.summary = summary;
    }

    public CharSequence getSummary() {
        return summary;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public boolean isEnabled() {
        return enabled;
    }
}
