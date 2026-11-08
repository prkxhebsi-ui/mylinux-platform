package android.os;

public final class Looper {
    private static final ThreadLocal<Looper> THREAD_LOCAL =
            new ThreadLocal<>();

    private static Looper mainLooper;

    private final MessageQueue queue;
    private final Thread thread;

    private Looper() {
        queue = new MessageQueue();
        thread = Thread.currentThread();
    }

    public static void prepare() {
        if (THREAD_LOCAL.get() != null) {
            throw new RuntimeException(
                    "Only one Looper per thread");
        }
        THREAD_LOCAL.set(new Looper());
    }

    public static void prepareMainLooper() {
        prepare();
        synchronized (Looper.class) {
            if (mainLooper != null) {
                throw new IllegalStateException(
                        "Main Looper already prepared");
            }
            mainLooper = myLooper();
        }
    }

    public static Looper getMainLooper() {
        return mainLooper;
    }

    public static Looper myLooper() {
        return THREAD_LOCAL.get();
    }

    public static MessageQueue myQueue() {
        Looper looper = myLooper();
        if (looper == null) {
            throw new RuntimeException("No Looper for this thread");
        }
        return looper.queue;
    }

    public MessageQueue getQueue() {
        return queue;
    }

    public Thread getThread() {
        return thread;
    }

    public static void loop() {
        Looper looper = myLooper();

        if (looper == null) {
            throw new RuntimeException(
                    "Looper.prepare() was not called");
        }

        MessageQueue queue = looper.queue;

        while (true) {
            Message message = queue.next();

            if (message == null) {
                return;
            }

            if (message.target != null) {
                message.target.dispatchMessage(message);
            }
        }
    }

    public void quit() {
        queue.quit();
    }

    public void quitSafely() {
        queue.quit();
    }

    public boolean isCurrentThread() {
        return Thread.currentThread() == thread;
    }
}
