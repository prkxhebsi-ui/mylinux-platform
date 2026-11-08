package com.android.server;

/** Foreground system-service thread. */
public final class FgThread {

    private static ServiceThread instance;

    private FgThread() {
    }

    public static synchronized ServiceThread get() {
        if (instance == null) {
            instance = new ServiceThread(
                    "android.fg", Thread.MAX_PRIORITY - 1);
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
