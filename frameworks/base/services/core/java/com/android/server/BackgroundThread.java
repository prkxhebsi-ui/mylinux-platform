package com.android.server;

/** Background system maintenance thread. */
public final class BackgroundThread {

    private static ServiceThread instance;

    private BackgroundThread() {
    }

    public static synchronized ServiceThread get() {
        if (instance == null) {
            instance = new ServiceThread(
                    "android.bg", Thread.MIN_PRIORITY + 1);
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
