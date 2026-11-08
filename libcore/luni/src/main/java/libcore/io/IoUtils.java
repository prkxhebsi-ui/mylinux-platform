package libcore.io;

import java.io.Closeable;
import java.io.IOException;

public final class IoUtils {
    private IoUtils() {}

    public static void closeQuietly(Closeable closeable) {
        if (closeable == null) return;

        try {
            closeable.close();
        } catch (IOException ignored) {
        }
    }

    public static void closeOrThrow(Closeable closeable)
            throws IOException {
        if (closeable != null) {
            closeable.close();
        }
    }
}
