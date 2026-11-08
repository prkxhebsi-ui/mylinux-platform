package android.content.pm;

public class ConfigurationInfo {
    public int reqTouchScreen;
    public int reqKeyboardType;
    public int reqNavigation;
    public int reqInputFeatures;
    public int reqGlEsVersion;

    public static final int INPUT_FEATURE_HARD_KEYBOARD = 1;
    public static final int INPUT_FEATURE_FIVE_WAY_NAV = 2;

    public static final int TOUCHSCREEN_NOTOUCH = 1;
    public static final int TOUCHSCREEN_STYLUS = 2;
    public static final int TOUCHSCREEN_FINGER = 3;

    public static final int KEYBOARD_NOKEYS = 1;
    public static final int KEYBOARD_QWERTY = 2;
    public static final int KEYBOARD_12KEY = 3;

    public static final int NAVIGATION_NONAV = 1;
    public static final int NAVIGATION_DPAD = 2;
    public static final int NAVIGATION_TRACKBALL = 3;
    public static final int NAVIGATION_WHEEL = 4;
}
