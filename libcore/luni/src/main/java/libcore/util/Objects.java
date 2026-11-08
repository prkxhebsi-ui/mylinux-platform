package libcore.util;

import java.util.Comparator;

/**
 * Utility methods for working with objects.
 *
 * This class belongs to libcore's internal namespace.
 */
public final class Objects {
    private Objects() {
        throw new AssertionError("No instances");
    }

    public static boolean equal(Object first, Object second) {
        return first == second ||
                (first != null && first.equals(second));
    }

    public static int hashCode(Object object) {
        return object == null ? 0 : object.hashCode();
    }

    public static int compare(
            Object first, Object second, Comparator<Object> comparator) {
        if (first == second) {
            return 0;
        }
        if (first == null) {
            return -1;
        }
        if (second == null) {
            return 1;
        }
        return comparator.compare(first, second);
    }

    public static <T> T requireNonNull(T object) {
        if (object == null) {
            throw new NullPointerException();
        }
        return object;
    }

    public static <T> T requireNonNull(T object, String message) {
        if (object == null) {
            throw new NullPointerException(message);
        }
        return object;
    }
}
