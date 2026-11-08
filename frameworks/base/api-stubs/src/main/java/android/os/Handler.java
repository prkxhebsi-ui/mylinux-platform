package android.os;

public class Handler {

    public interface Callback {
        boolean handleMessage(Message message);
    }

    private final Looper looper;
    private final MessageQueue queue;
    private final Callback callback;

    public Handler() {
        this(null, false);
    }

    public Handler(Looper looper) {
        this(looper, null);
    }

    public Handler(Looper looper, Callback callback) {
        if (looper == null) {
            looper = Looper.myLooper();
        }

        if (looper == null) {
            throw new RuntimeException("No Looper for this thread");
        }

        this.looper = looper;
        this.queue = looper.getQueue();
        this.callback = callback;
    }

    private Handler(Callback callback, boolean async) {
        this(Looper.myLooper(), callback);
    }

    public Looper getLooper() {
        return looper;
    }

    public void handleMessage(Message message) {}

    public void dispatchMessage(Message message) {
        if (message.callback != null) {
            message.callback.run();
        } else if (callback == null ||
                !callback.handleMessage(message)) {
            handleMessage(message);
        }
    }

    public boolean post(Runnable runnable) {
        return postDelayed(runnable, 0);
    }

    public boolean postDelayed(Runnable runnable, long delayMillis) {
        if (runnable == null) return false;

        Message message = Message.obtain(this, runnable);
        return sendMessageDelayed(message, delayMillis);
    }

    public boolean postAtTime(Runnable runnable, long uptimeMillis) {
        if (runnable == null) return false;

        Message message = Message.obtain(this, runnable);
        return sendMessageAtTime(message, uptimeMillis);
    }

    public boolean postAtFrontOfQueue(Runnable runnable) {
        if (runnable == null) return false;

        Message message = Message.obtain(this, runnable);
        return sendMessageAtFrontOfQueue(message);
    }

    public void removeCallbacks(Runnable runnable) {
        queue.removeCallbacks(this, runnable);
    }

    public boolean sendMessage(Message message) {
        return sendMessageDelayed(message, 0);
    }

    public boolean sendEmptyMessage(int what) {
        return sendMessage(Message.obtain(this, what));
    }

    public boolean sendEmptyMessageDelayed(int what, long delay) {
        return sendMessageDelayed(
                Message.obtain(this, what), delay);
    }

    public boolean sendMessageDelayed(Message message, long delay) {
        if (delay < 0) delay = 0;

        long when = System.nanoTime() / 1000000L + delay;
        return sendMessageAtTime(message, when);
    }

    public boolean sendMessageAtTime(Message message, long uptimeMillis) {
        if (message == null) return false;

        message.target = this;
        return queue.enqueueMessage(message, uptimeMillis);
    }

    public boolean sendMessageAtFrontOfQueue(Message message) {
        if (message == null) return false;

        message.target = this;
        return queue.enqueueMessage(message, 0);
    }

    public void removeMessages(int what) {
        queue.removeMessages(this, what);
    }

    public boolean hasMessages(int what) {
        return queue.hasMessages(this, what);
    }

    public String getMessageName(Message message) {
        if (message.callback != null) {
            return message.callback.getClass().getName();
        }
        return "0x" + Integer.toHexString(message.what);
    }
}
