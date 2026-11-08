package android.animation;

public abstract class Animator {
    public abstract void start();
    public abstract void cancel();
    public abstract void end();

    public boolean isRunning() {
        throw new RuntimeException("Stub!");
    }

    public boolean isStarted() {
        throw new RuntimeException("Stub!");
    }

    public void setDuration(long duration) {
        throw new RuntimeException("Stub!");
    }
}
