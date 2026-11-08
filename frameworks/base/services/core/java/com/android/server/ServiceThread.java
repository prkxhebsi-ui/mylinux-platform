package com.android.server;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * MyLinux system service worker thread.
 *
 * Provides a serialized task queue for system services.
 */
public class ServiceThread extends Thread {

    private static final Runnable STOP = new Runnable() {
        @Override
        public void run() {
        }
    };

    private final BlockingQueue<Runnable> queue =
            new LinkedBlockingQueue<Runnable>();

    private final CountDownLatch ready =
            new CountDownLatch(1);

    private volatile boolean acceptingTasks = true;
    private volatile boolean running = false;

    public ServiceThread(String name) {
        this(name, Thread.NORM_PRIORITY);
    }

    public ServiceThread(String name, int priority) {
        super(name);

        if (priority < Thread.MIN_PRIORITY ||
                priority > Thread.MAX_PRIORITY) {
            throw new IllegalArgumentException("Invalid thread priority");
        }

        setPriority(priority);
        setDaemon(true);
    }

    public synchronized void startAndWait() {
        if (getState() != State.NEW) {
            throw new IllegalStateException("Thread already started");
        }

        start();

        try {
            ready.await();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IllegalStateException(
                    "Interrupted while starting " + getName(), e);
        }
    }

    public synchronized boolean post(Runnable task) {
        if (task == null || !acceptingTasks) {
            return false;
        }

        return queue.offer(task);
    }

    public synchronized void quitSafely() {
        if (!acceptingTasks) {
            return;
        }

        acceptingTasks = false;
        queue.offer(STOP);
    }

    public synchronized void quit() {
        acceptingTasks = false;
        queue.clear();
        queue.offer(STOP);
    }

    public boolean isRunning() {
        return running;
    }

    public boolean isAcceptingTasks() {
        return acceptingTasks;
    }

    public int getPendingTaskCount() {
        return queue.size();
    }

    public boolean awaitTermination(long timeoutMillis) {
        try {
            join(timeoutMillis);
            return !isAlive();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return false;
        }
    }

    @Override
    public void run() {
        running = true;
        ready.countDown();

        try {
            while (true) {
                Runnable task = queue.take();

                if (task == STOP) {
                    break;
                }

                try {
                    task.run();
                } catch (Throwable error) {
                    System.err.println(
                            "ServiceThread task failed: " + getName());
                    error.printStackTrace();
                }
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            running = false;
            acceptingTasks = false;
        }
    }
}
