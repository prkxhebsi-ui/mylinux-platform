package android.os;

public final class SystemClock {
    private SystemClock() {}

    public static long uptimeMillis() {
        return System.nanoTime() / 1000000L;
    }

    public static long uptimeNanos() {
        return System.nanoTime();
    }

    public static long elapsedRealtime() {
        return System.nanoTime() / 1000000L;
    }

    public static long elapsedRealtimeNanos() {
        return System.nanoTime();
    }

    public static long currentThreadTimeMillis() {
        return java.lang.management.ManagementFactory
                .getThreadMXBean()
                .getCurrentThreadCpuTime() / 1000000L;
    }

    public static long currentThreadTimeMicro() {
        return java.lang.management.ManagementFactory
                .getThreadMXBean()
                .getCurrentThreadCpuTime() / 1000L;
    }

    public static void sleep(long millis) {
        if (millis <= 0) return;

        long deadline = System.nanoTime() + millis * 1000000L;

        while (true) {
            long remaining = deadline - System.nanoTime();
            if (remaining <= 0) return;

            try {
                Thread.sleep(
                    remaining / 1000000L,
                    (int) (remaining % 1000000L)
                );
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    public static void yield() {
        Thread.yield();
    }
}
