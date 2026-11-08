package android.view;

public interface WindowManager {

    int DOCKED_INVALID = -1;

    void addView(View view, ViewGroup.LayoutParams params);

    void updateViewLayout(View view, ViewGroup.LayoutParams params);

    void removeView(View view);

    void removeViewImmediate(View view);

    class LayoutParams extends ViewGroup.LayoutParams {

        public static final int TYPE_BASE_APPLICATION = 1;
        public static final int TYPE_APPLICATION = 2;
        public static final int TYPE_APPLICATION_STARTING = 3;
        public static final int TYPE_APPLICATION_PANEL = 1000;
        public static final int TYPE_APPLICATION_MEDIA = 1001;
        public static final int TYPE_APPLICATION_SUB_PANEL = 1002;
        public static final int TYPE_APPLICATION_ATTACHED_DIALOG = 1003;
        public static final int TYPE_APPLICATION_MEDIA_OVERLAY = 1004;
        public static final int TYPE_APPLICATION_ABOVE_SUB_PANEL = 1005;

        public static final int TYPE_STATUS_BAR = 2000;
        public static final int TYPE_SEARCH_BAR = 2001;
        public static final int TYPE_PHONE = 2002;
        public static final int TYPE_SYSTEM_ALERT = 2003;
        public static final int TYPE_KEYGUARD = 2004;
        public static final int TYPE_TOAST = 2005;
        public static final int TYPE_SYSTEM_OVERLAY = 2006;
        public static final int TYPE_PRIORITY_PHONE = 2007;
        public static final int TYPE_SYSTEM_DIALOG = 2008;
        public static final int TYPE_KEYGUARD_DIALOG = 2009;
        public static final int TYPE_SYSTEM_ERROR = 2010;
        public static final int TYPE_INPUT_METHOD = 2011;
        public static final int TYPE_INPUT_METHOD_DIALOG = 2012;
        public static final int TYPE_WALLPAPER = 2013;
        public static final int TYPE_STATUS_BAR_PANEL = 2014;
        public static final int TYPE_SECURE_SYSTEM_OVERLAY = 2015;
        public static final int TYPE_DRAG = 2016;
        public static final int TYPE_STATUS_BAR_SUB_PANEL = 2017;
        public static final int TYPE_POINTER = 2018;
        public static final int TYPE_NAVIGATION_BAR = 2019;
        public static final int TYPE_VOLUME_OVERLAY = 2020;
        public static final int TYPE_BOOT_PROGRESS = 2021;
        public static final int TYPE_INPUT_CONSUMER = 2022;
        public static final int TYPE_NAVIGATION_BAR_PANEL = 2024;
        public static final int TYPE_DISPLAY_OVERLAY = 2026;
        public static final int TYPE_PRIVATE_PRESENTATION = 2030;
        public static final int TYPE_VOICE_INTERACTION = 2031;
        public static final int TYPE_ACCESSIBILITY_OVERLAY = 2032;
        public static final int TYPE_APPLICATION_OVERLAY = 2038;

        public static final int FLAG_ALLOW_LOCK_WHILE_SCREEN_ON = 0x00000001;
        public static final int FLAG_DIM_BEHIND = 0x00000002;
        public static final int FLAG_BLUR_BEHIND = 0x00000004;
        public static final int FLAG_NOT_FOCUSABLE = 0x00000008;
        public static final int FLAG_NOT_TOUCHABLE = 0x00000010;
        public static final int FLAG_NOT_TOUCH_MODAL = 0x00000020;
        public static final int FLAG_TOUCHABLE_WHEN_WAKING = 0x00000040;
        public static final int FLAG_KEEP_SCREEN_ON = 0x00000080;
        public static final int FLAG_LAYOUT_IN_SCREEN = 0x00000100;
        public static final int FLAG_LAYOUT_NO_LIMITS = 0x00000200;
        public static final int FLAG_FULLSCREEN = 0x00000400;
        public static final int FLAG_FORCE_NOT_FULLSCREEN = 0x00000800;
        public static final int FLAG_DITHER = 0x00001000;
        public static final int FLAG_SECURE = 0x00002000;
        public static final int FLAG_SCALED = 0x00004000;
        public static final int FLAG_IGNORE_CHEEK_PRESSES = 0x00008000;
        public static final int FLAG_LAYOUT_INSET_DECOR = 0x00010000;
        public static final int FLAG_ALT_FOCUSABLE_IM = 0x00020000;
        public static final int FLAG_WATCH_OUTSIDE_TOUCH = 0x00040000;
        public static final int FLAG_SHOW_WHEN_LOCKED = 0x00080000;
        public static final int FLAG_SHOW_WALLPAPER = 0x00100000;
        public static final int FLAG_TURN_SCREEN_ON = 0x00200000;
        public static final int FLAG_DISMISS_KEYGUARD = 0x00400000;
        public static final int FLAG_SPLIT_TOUCH = 0x00800000;
        public static final int FLAG_HARDWARE_ACCELERATED = 0x01000000;
        public static final int FLAG_LAYOUT_IN_OVERSCAN = 0x02000000;
        public static final int FLAG_TRANSLUCENT_STATUS = 0x04000000;
        public static final int FLAG_TRANSLUCENT_NAVIGATION = 0x08000000;
        public static final int FLAG_LOCAL_FOCUS_MODE = 0x10000000;
        public static final int FLAG_SHOW_WALLPAPER = 0x00100000;
        public static final int FLAG_LAYOUT_ATTACHED_IN_DECOR = 0x40000000;

        public static final int SOFT_INPUT_MASK_STATE = 0x0f;
        public static final int SOFT_INPUT_STATE_UNSPECIFIED = 0;
        public static final int SOFT_INPUT_STATE_UNCHANGED = 1;
        public static final int SOFT_INPUT_STATE_HIDDEN = 2;
        public static final int SOFT_INPUT_STATE_ALWAYS_HIDDEN = 3;
        public static final int SOFT_INPUT_STATE_VISIBLE = 4;
        public static final int SOFT_INPUT_STATE_ALWAYS_VISIBLE = 5;

        public static final int SOFT_INPUT_MASK_ADJUST = 0xf0;
        public static final int SOFT_INPUT_ADJUST_UNSPECIFIED = 0x00;
        public static final int SOFT_INPUT_ADJUST_RESIZE = 0x10;
        public static final int SOFT_INPUT_ADJUST_PAN = 0x20;
        public static final int SOFT_INPUT_ADJUST_NOTHING = 0x30;

        public int x;
        public int y;
        public int type;
        public int flags;
        public int privateFlags;
        public int gravity;
        public int softInputMode;
        public int screenOrientation;
        public int windowAnimations;
        public float alpha = 1.0f;
        public float dimAmount = 1.0f;
        public String packageName;
        public CharSequence title;
        public Object token;

        public LayoutParams() {
            this(MATCH_PARENT, MATCH_PARENT);
        }

        public LayoutParams(int width, int height) {
            super(width, height);
            this.type = TYPE_APPLICATION;
            this.gravity = Gravity.TOP | Gravity.START;
        }

        public LayoutParams(int width, int height, int type,
                int flags, int pixelFormat) {
            this(width, height);
            this.type = type;
            this.flags = flags;
        }

        public void setTitle(CharSequence title) {
            this.title = title;
        }
    }
}
