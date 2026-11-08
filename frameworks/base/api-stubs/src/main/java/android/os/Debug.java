package android.os;

import java.util.Map;

public final class Debug {
    private Debug() {}

    public static class MemoryInfo {
        public int dalvikPss;
        public int nativePss;
        public int otherPss;
        public int dalvikPrivateDirty;
        public int nativePrivateDirty;
        public int otherPrivateDirty;
        public int dalvikSharedDirty;
        public int nativeSharedDirty;
        public int otherSharedDirty;
        public int getTotalPss() {
            return dalvikPss + nativePss + otherPss;
        }
    }

    public static void startMethodTracing() {
        throw new UnsupportedOperationException("API stub");
    }

    public static void startMethodTracing(String name) {
        throw new UnsupportedOperationException("API stub");
    }

    public static void stopMethodTracing() {
        throw new UnsupportedOperationException("API stub");
    }

    public static boolean isDebuggerConnected() {
        return false;
    }

    public static void waitingForDebugger() {}

    public static void waitForDebugger() {}

    public static long threadCpuTimeNanos() {
        return -1;
    }

    public static long getNativeHeapSize() {
        return 0;
    }

    public static long getNativeHeapAllocatedSize() {
        return 0;
    }

    public static long getNativeHeapFreeSize() {
        return 0;
    }

    public static void getMemoryInfo(MemoryInfo info) {
        if (info == null) {
            throw new IllegalArgumentException("MemoryInfo is null");
        }
        throw new UnsupportedOperationException("API stub");
    }

    public static Map<String, String> getMemoryStats() {
        throw new UnsupportedOperationException("API stub");
    }
}
