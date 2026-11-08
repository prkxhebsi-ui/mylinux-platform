package android.view.accessibility;

public class AccessibilityNodeInfo {
    public static final int ACTION_CLICK = 0x00000010;
    public static final int ACTION_FOCUS = 0x00000001;
    public static final int ACTION_CLEAR_FOCUS = 0x00000002;

    public boolean performAction(int action) {
        throw new RuntimeException("Stub!");
    }

    public CharSequence getText() {
        throw new RuntimeException("Stub!");
    }

    public CharSequence getContentDescription() {
        throw new RuntimeException("Stub!");
    }

    public void recycle() {
        throw new RuntimeException("Stub!");
    }
}
