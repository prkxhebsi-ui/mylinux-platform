package android.view;

/**
 * Android-compatible gravity constants.
 * API target: 30
 */
public final class Gravity {

    private Gravity() {}

    public static final int NO_GRAVITY = 0x0000;

    public static final int AXIS_SPECIFIED = 0x0001;
    public static final int AXIS_PULL_BEFORE = 0x0002;
    public static final int AXIS_PULL_AFTER = 0x0004;
    public static final int AXIS_CLIP = 0x0008;

    public static final int AXIS_X_SHIFT = 0;
    public static final int AXIS_Y_SHIFT = 4;

    public static final int TOP = (AXIS_PULL_BEFORE | AXIS_SPECIFIED)
            << AXIS_Y_SHIFT;

    public static final int BOTTOM = (AXIS_PULL_AFTER | AXIS_SPECIFIED)
            << AXIS_Y_SHIFT;

    public static final int LEFT = (AXIS_PULL_BEFORE | AXIS_SPECIFIED)
            << AXIS_X_SHIFT;

    public static final int RIGHT = (AXIS_PULL_AFTER | AXIS_SPECIFIED)
            << AXIS_X_SHIFT;

    public static final int CENTER_VERTICAL = AXIS_SPECIFIED
            << AXIS_Y_SHIFT;

    public static final int FILL_VERTICAL = TOP | BOTTOM;

    public static final int CENTER_HORIZONTAL = AXIS_SPECIFIED
            << AXIS_X_SHIFT;

    public static final int FILL_HORIZONTAL = LEFT | RIGHT;

    public static final int CENTER = CENTER_VERTICAL | CENTER_HORIZONTAL;

    public static final int FILL = FILL_VERTICAL | FILL_HORIZONTAL;

    public static final int CLIP_VERTICAL =
            AXIS_CLIP << AXIS_Y_SHIFT;

    public static final int CLIP_HORIZONTAL =
            AXIS_CLIP << AXIS_X_SHIFT;

    public static final int RELATIVE_LAYOUT_DIRECTION = 0x00800000;

    public static final int START =
            RELATIVE_LAYOUT_DIRECTION | LEFT;

    public static final int END =
            RELATIVE_LAYOUT_DIRECTION | RIGHT;

    public static final int HORIZONTAL_GRAVITY_MASK = 0x0007;
    public static final int VERTICAL_GRAVITY_MASK = 0x0070;
    public static final int RELATIVE_HORIZONTAL_GRAVITY_MASK =
            0x00800007;

    public static final int DISPLAY_CLIP_HORIZONTAL = 0x01000000;
    public static final int DISPLAY_CLIP_VERTICAL = 0x10000000;

    public static final int DISPLAY_CLIP_MASK =
            DISPLAY_CLIP_HORIZONTAL | DISPLAY_CLIP_VERTICAL;

    public static final int LEFT_RIGHT = LEFT | RIGHT;
    public static final int TOP_BOTTOM = TOP | BOTTOM;

    public static final int HORIZONTAL = LEFT | RIGHT;
    public static final int VERTICAL = TOP | BOTTOM;


    public static final int LAYOUT_DIRECTION_LTR = 0;
    public static final int LAYOUT_DIRECTION_RTL = 1;

    /**
     * Convert START and END into LEFT and RIGHT.
     */
    public static int getAbsoluteGravity(
            int gravity, int layoutDirection) {

        if ((gravity & RELATIVE_LAYOUT_DIRECTION) == 0) {
            return gravity;
        }

        boolean isRtl = layoutDirection == LAYOUT_DIRECTION_RTL;
        boolean hasStart = (gravity & START) == START;
        boolean hasEnd = (gravity & END) == END;

        int result = gravity & ~RELATIVE_HORIZONTAL_GRAVITY_MASK;

        if (hasStart) {
            result |= isRtl ? RIGHT : LEFT;
        }

        if (hasEnd) {
            result |= isRtl ? LEFT : RIGHT;
        }

        return result;
    }
}
