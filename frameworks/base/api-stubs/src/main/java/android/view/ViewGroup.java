package android.view;

import android.content.Context;

public abstract class ViewGroup extends View {
    public ViewGroup(Context context) {
        super(context);
    }

    public static class LayoutParams {
        public static final int MATCH_PARENT = -1;
        public static final int WRAP_CONTENT = -2;

        public int width;
        public int height;

        public LayoutParams(int width, int height) {
            this.width = width;
            this.height = height;
        }
    }

    public void addView(View child) {
        throw new UnsupportedOperationException("API stub");
    }

    public void removeView(View child) {
        throw new UnsupportedOperationException("API stub");
    }
}
