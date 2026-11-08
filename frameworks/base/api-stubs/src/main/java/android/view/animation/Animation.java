package android.view.animation;

public abstract class Animation {
    public static final int INFINITE = -1;
    public static final int RESTART = 1;
    public static final int REVERSE = 2;

    public void start() {
        throw new RuntimeException("Stub!");
    }

    public void cancel() {
        throw new RuntimeException("Stub!");
    }

    public boolean hasEnded() {
        throw new RuntimeException("Stub!");
    }

    public void setDuration(long durationMillis) {
        throw new RuntimeException("Stub!");
    }
}
