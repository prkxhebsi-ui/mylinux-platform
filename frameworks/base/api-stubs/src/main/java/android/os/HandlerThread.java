package android.os;

public class HandlerThread extends Thread {
    private Looper looper;
    private final int priority;
    private int threadId;

    public HandlerThread(String name) {
        this(name, Thread.NORM_PRIORITY);
    }

    public HandlerThread(String name, int priority) {
        super(name);
        this.priority = priority;
    }

    @Override
    public void run() {
        threadId = (int) Thread.currentThread().getId();

        Looper.prepare();

        synchronized (this) {
            looper = Looper.myLooper();
            notifyAll();
        }

        onLooperPrepared();
        Looper.loop();
    }

    protected void onLooperPrepared() {}

    public Looper getLooper() {
        if (!isAlive()) return null;

        synchronized (this) {
            while (isAlive() && looper == null) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return null;
                }
            }
        }

        return looper;
    }

    public int getThreadId() {
        return threadId;
    }

    public boolean quit() {
        Looper current = getLooper();
        if (current == null) return false;
        current.quit();
        return true;
    }

    public boolean quitSafely() {
        Looper current = getLooper();
        if (current == null) return false;
        current.quitSafely();
        return true;
    }

    public int getThreadPriority() {
        return priority;
    }
}
