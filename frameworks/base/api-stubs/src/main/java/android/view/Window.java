package android.view;

import android.content.Context;

public abstract class Window {

    public static final int FEATURE_OPTIONS_PANEL = 0;
    public static final int FEATURE_NO_TITLE = 1;
    public static final int FEATURE_PROGRESS = 2;
    public static final int FEATURE_LEFT_ICON = 3;
    public static final int FEATURE_RIGHT_ICON = 4;
    public static final int FEATURE_INDETERMINATE_PROGRESS = 5;
    public static final int FEATURE_CONTEXT_MENU = 6;
    public static final int FEATURE_CUSTOM_TITLE = 7;
    public static final int FEATURE_ACTION_BAR = 8;
    public static final int FEATURE_ACTION_BAR_OVERLAY = 9;
    public static final int FEATURE_ACTION_MODE_OVERLAY = 10;

    protected final Context context;
    private WindowManager.LayoutParams attributes;
    private View decorView;
    private Callback callback;

    protected Window(Context context) {
        this.context = context;
        this.attributes = new WindowManager.LayoutParams();
    }

    public Context getContext() {
        return context;
    }

    public abstract void takeSurface(Object callback);

    public abstract void takeInputQueue(Object callback);

    public abstract boolean isFloating();

    public abstract void setContentView(int layoutResID);

    public abstract void setContentView(View view);

    public abstract void addContentView(
            View view, ViewGroup.LayoutParams params);

    public abstract View getCurrentFocus();

    public abstract void setTitle(CharSequence title);

    public abstract void setTitleColor(int textColor);

    public abstract void openPanel(int featureId, Object event);

    public abstract void closePanel(int featureId);

    public abstract void invalidatePanelMenu(int featureId);

    public abstract void setFeatureDrawableResource(
            int featureId, int resId);

    public abstract void setFeatureDrawableUri(
            int featureId, android.net.Uri uri);

    public abstract void setFeatureDrawable(
            int featureId, Object drawable);

    public abstract void setFeatureDrawableAlpha(
            int featureId, int alpha);

    public abstract void setFlags(int flags, int mask);

    public abstract void setSoftInputMode(int mode);

    public abstract void setBackgroundDrawable(Object drawable);

    public abstract void setNavigationBarColor(int color);

    public abstract void setStatusBarColor(int color);

    public abstract void setDecorView(View decor);

    public abstract void setWindowManager(
            WindowManager windowManager,
            Object appToken,
            String appName);

    public abstract void setWindowManager(
            WindowManager windowManager,
            Object appToken,
            String appName,
            boolean hardwareAccelerated);

    public abstract void setContainer(Window container);

    public abstract void setWindowAnimations(int resId);

    public abstract void setDimAmount(float amount);

    public abstract void setLayout(int width, int height);

    public abstract void setGravity(int gravity);

    public abstract void setType(int type);

    public abstract void addFlags(int flags);

    public abstract void clearFlags(int flags);

    public abstract void setAttributes(
            WindowManager.LayoutParams attributes);

    public abstract WindowManager.LayoutParams getAttributes();

    public abstract View getDecorView();

    public abstract void setCallback(Callback callback);

    public abstract Callback getCallback();

    public interface Callback {
        boolean dispatchKeyEvent(Object event);
        boolean dispatchTouchEvent(Object event);
        void onWindowFocusChanged(boolean hasFocus);
    }
}
