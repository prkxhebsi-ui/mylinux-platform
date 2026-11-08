package com.android.server;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public final class SystemServerInitThreadPool {

    private static final AtomicBoolean INITIALIZED =
            new AtomicBoolean(false);

    private static ExecutorService executor;

    private SystemServerInitThreadPool() {
    }

    public static synchronized void start() {
        if (!INITIALIZED.compareAndSet(false, true)) {
            throw new IllegalStateException("Thread pool already started");
        }

        executor = Executors.newFixedThreadPool(
                Math.max(2, Runtime.getRuntime().availableProcessors()));
    }

    public static synchronized Future<?> submit(
            Runnable task, String description) {

        if (!INITIALIZED.get() || executor == null) {
            throw new IllegalStateException("Thread pool not started");
        }

        if (task == null) {
            throw new IllegalArgumentException("Task is null");
        }

        return executor.submit(() -> {
            try {
                task.run();
            } catch (Throwable error) {
                System.err.println(
                        "SystemServer task failed: " + description);
                error.printStackTrace();
                throw error;
            }
        });
    }

    public static synchronized void shutdown() {
        if (executor == null) {
            return;
        }

        executor.shutdown();

        try {
            if (!executor.awaitTermination(30, TimeUnit.SECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
            Thread.currentThread().interrupt();
        }

        executor = null;
        INITIALIZED.set(false);
    }
}
