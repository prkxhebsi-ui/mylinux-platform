package android.content.pm;

public class ManifestIntentFilter {
    public String name;
    public String[] actions;
    public String[] categories;
    public ManifestData[] data;
    public int priority;
    public boolean autoVerify;
    public boolean visibleToInstantApps;

    public boolean hasAction(String action) {
        if (actions == null || action == null) return false;
        for (int i = 0; i < actions.length; i++) {
            if (action.equals(actions[i])) return true;
        }
        return false;
    }

    public boolean hasCategory(String category) {
        if (categories == null || category == null) return false;
        for (int i = 0; i < categories.length; i++) {
            if (category.equals(categories[i])) return true;
        }
        return false;
    }
}
