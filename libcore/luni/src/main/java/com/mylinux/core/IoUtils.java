package com.mylinux.core;

import java.io.Closeable;
import java.io.IOException;

/** I/O helpers for MyLinux-owned Java code. */
public final class IoUtils {
    private IoUtils() {
    }

    public static void closeQuietly(Closeable closeable) {
        if (closeable == null) {
            return;
        }

        try {
            closeable.close();
        } catch (IOException ignored) {
            // Best-effort cleanup; callers needing errors should close directly.
        }
    }

    public static void closeOrThrow(Closeable closeable) throws IOException {
        if (closeable != null) {
            closeable.close();
        }
    }
}
