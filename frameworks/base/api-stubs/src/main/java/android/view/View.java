package android.view;

import android.content.Context;

public class View {
    protected final Context context;
    private int id;
    private int visibility = VISIBLE;

    public static final int VISIBLE = 0;
    public static final int INVISIBLE = 4;
    public static final int GONE = 8;

    public View(Context context) {
        this.context = context;
    }

    public Context getContext() {
        return context;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void setVisibility(int visibility) {
        this.visibility = visibility;
    }

    public int getVisibility() {
        return visibility;
    }

    public void setEnabled(boolean enabled) {}
    public boolean isEnabled() { return true; }

    public void setOnClickListener(OnClickListener listener) {}

    public interface OnClickListener {
        void onClick(View view);
    }

    public static class MeasureSpec {
        public static final int UNSPECIFIED = 0;
        public static final int EXACTLY = 0x40000000;
        public static final int AT_MOST = 0x80000000;

        public static int makeMeasureSpec(int size, int mode) {
            return size | mode;
        }

        public static int getSize(int measureSpec) {
            return measureSpec & 0x3fffffff;
        }

        public static int getMode(int measureSpec) {
            return measureSpec & 0xc0000000;
        }
    }
}
