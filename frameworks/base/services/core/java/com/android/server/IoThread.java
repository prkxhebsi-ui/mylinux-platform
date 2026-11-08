package com.android.server;

/** Dedicated system-service I/O thread. */
public final class IoThread {

    private static ServiceThread instance;

    private IoThread() {
    }

    public static synchronized ServiceThread get() {
        if (instance == null) {
            instance = new ServiceThread(
                    "android.io", Thread.NORM_PRIORITY);
            instance.startAndWait();
        }

        return instance;
    }

    public static synchronized void shutdownForTest() {
        if (instance != null) {
            instance.quitSafely();
            instance = null;
        }
    }
}
