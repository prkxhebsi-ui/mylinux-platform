package android.os;

public final class Process {
    private Process() {}

    public static final int SYSTEM_UID = 1000;
    public static final int ROOT_UID = 0;
    public static final int PHONE_UID = 1001;
    public static final int SHELL_UID = 2000;
    public static final int INVALID_UID = -1;

    public static int myPid() {
        return 0;
    }

    public static int myUid() {
        return 0;
    }

    public static int myTid() {
        return 0;
    }

    public static boolean is64Bit() {
        return false;
    }

    public static void killProcess(int pid) {}

    public static void sendSignal(int pid, int signal) {}

    public static int getThreadPriority(int tid) {
        return 0;
    }

    public static void setThreadPriority(int priority) {}

    public static void setThreadPriority(int tid, int priority) {}
}
