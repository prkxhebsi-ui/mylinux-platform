package android.util;

public final class Log {
    private Log() {}

    public static int v(String tag, String message) {
        return 0;
    }

    public static int d(String tag, String message) {
        return 0;
    }

    public static int i(String tag, String message) {
        return 0;
    }

    public static int w(String tag, String message) {
        return 0;
    }

    public static int e(String tag, String message) {
        return 0;
    }

    public static int d(String tag, String message, Throwable error) {
        return 0;
    }

    public static int i(String tag, String message, Throwable error) {
        return 0;
    }

    public static int w(String tag, String message, Throwable error) {
        return 0;
    }

    public static int e(String tag, String message, Throwable error) {
        return 0;
    }

    public static int wtf(String tag, String message) {
        return 0;
    }

    public static int wtf(String tag, String message, Throwable error) {
        return 0;
    }

    public static String getStackTraceString(Throwable error) {
        return error == null ? "" : error.toString();
    }
}
