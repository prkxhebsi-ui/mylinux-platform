package com.android.server;

/** Dedicated system UI-related worker thread. */
public final class UiThread {

    private static ServiceThread instance;

    private UiThread() {
    }

    public static synchronized ServiceThread get() {
        if (instance == null) {
            instance = new ServiceThread(
                    "android.ui", Thread.NORM_PRIORITY + 1);
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
