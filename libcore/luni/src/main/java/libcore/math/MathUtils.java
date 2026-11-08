package libcore.math;

/** Internal numeric helpers. */
public final class MathUtils {
    private MathUtils() {
        throw new AssertionError("No instances");
    }

    public static int addExact(int first, int second) {
        return Math.addExact(first, second);
    }

    public static long addExact(long first, long second) {
        return Math.addExact(first, second);
    }

    public static int clamp(int value, int minimum, int maximum) {
        if (minimum > maximum) {
            throw new IllegalArgumentException("minimum exceeds maximum");
        }
        return Math.max(minimum, Math.min(maximum, value));
    }

    public static long clamp(long value, long minimum, long maximum) {
        if (minimum > maximum) {
            throw new IllegalArgumentException("minimum exceeds maximum");
        }
        return Math.max(minimum, Math.min(maximum, value));
    }

    public static double clamp(
            double value, double minimum, double maximum) {
        if (Double.isNaN(value) ||
                Double.isNaN(minimum) ||
                Double.isNaN(maximum) ||
                minimum > maximum) {
            throw new IllegalArgumentException("Invalid clamp arguments");
        }
        return Math.max(minimum, Math.min(maximum, value));
    }
}
