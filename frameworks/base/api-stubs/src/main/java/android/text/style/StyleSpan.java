package android.text.style;

public class StyleSpan {
    public static final int NORMAL = 0;
    public static final int BOLD = 1;
    public static final int ITALIC = 2;
    public static final int BOLD_ITALIC = 3;

    private final int style;

    public StyleSpan(int style) {
        this.style = style;
    }

    public int getStyle() {
        return style;
    }
}
