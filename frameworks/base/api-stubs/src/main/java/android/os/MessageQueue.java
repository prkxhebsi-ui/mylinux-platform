package android.os;

import java.util.PriorityQueue;

public final class MessageQueue {
    private final PriorityQueue<Message> messages =
            new PriorityQueue<>(
                (a, b) -> Long.compare(a.when, b.when));

    private boolean quitting;

    public MessageQueue() {}

    public synchronized boolean enqueueMessage(
            Message message, long when) {
        if (quitting || message == null || message.target == null) {
            return false;
        }

        message.when = when;
        messages.offer(message);
        notifyAll();
        return true;
    }

    public synchronized Message next() {
        while (!quitting) {
            Message message = messages.peek();

            if (message == null) {
                waitForMessage(0);
                continue;
            }

            long delay = message.when - System.nanoTime() / 1000000L;

            if (delay > 0) {
                waitForMessage(delay);
                continue;
            }

            return messages.poll();
        }

        return null;
    }

    private void waitForMessage(long millis) {
        try {
            if (millis <= 0) wait();
            else wait(millis);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            quitting = true;
        }
    }

    public synchronized void removeCallbacks(
            Handler handler, Runnable callback) {
        messages.removeIf(m ->
                m.target == handler && m.callback == callback);
    }

    public synchronized void removeMessages(
            Handler handler, int what) {
        messages.removeIf(m ->
                m.target == handler &&
                m.what == what &&
                m.callback == null);
    }

    public synchronized boolean hasMessages(
            Handler handler, int what) {
        for (Message message : messages) {
            if (message.target == handler &&
                    message.what == what &&
                    message.callback == null) {
                return true;
            }
        }
        return false;
    }

    public synchronized void quit() {
        quitting = true;
        messages.clear();
        notifyAll();
    }

    public synchronized boolean isQuitting() {
        return quitting;
    }
}
