package android.accessibilityservice;

public abstract class AccessibilityService {
    public static final int GLOBAL_ACTION_BACK = 1;
    public static final int GLOBAL_ACTION_HOME = 2;
    public static final int GLOBAL_ACTION_RECENTS = 3;

    public abstract void onAccessibilityEvent(Object event);
    public abstract void onInterrupt();

    public boolean performGlobalAction(int action) {
        throw new RuntimeException("Stub!");
    }
}
