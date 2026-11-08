package android.graphics.drawable;

public abstract class Drawable {
    public abstract void draw(Object canvas);

    public void setAlpha(int alpha) {
        throw new RuntimeException("Stub!");
    }

    public void setBounds(int left, int top, int right, int bottom) {
        throw new RuntimeException("Stub!");
    }

    public int getIntrinsicWidth() {
        throw new RuntimeException("Stub!");
    }

    public int getIntrinsicHeight() {
        throw new RuntimeException("Stub!");
    }
}
