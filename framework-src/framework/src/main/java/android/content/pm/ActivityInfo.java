package android.content.pm;

public class ActivityInfo extends ComponentInfo {
    public String parentActivityName;
    public String targetActivity;
    public String taskAffinity;
    public String theme;
    public int launchMode;
    public int screenOrientation;
    public int configChanges;
    public int softInputMode;

    public static final int LAUNCH_MULTIPLE = 0;
    public static final int LAUNCH_SINGLE_TOP = 1;
    public static final int LAUNCH_SINGLE_TASK = 2;
    public static final int LAUNCH_SINGLE_INSTANCE = 3;

    public static final int SCREEN_ORIENTATION_UNSPECIFIED = -1;
    public static final int SCREEN_ORIENTATION_LANDSCAPE = 0;
    public static final int SCREEN_ORIENTATION_PORTRAIT = 1;
}
