package com.mylinux.internal.os;

import java.io.IOException;

/**
 * Native interface for MyLinux Zygote.
 *
 * This class communicates with the native Zygote JNI library.
 */
public final class NativeZygote {

    private static boolean loaded;

    static {
        try {
            System.loadLibrary("mylinux_zygote_jni");
            loaded = true;
        } catch (UnsatisfiedLinkError error) {
            loaded = false;
        }
    }

    private NativeZygote() {
    }

    private static native int nativeGetServerSocketFd(
            String socketName
    );

    public static boolean isNativeLoaded() {
        return loaded;
    }

    public static int getServerSocketFd(String socketName)
            throws IOException {

        if (!loaded) {
            throw new IOException(
                "MyLinux Zygote JNI library is unavailable"
            );
        }

        if (socketName == null || socketName.isEmpty()) {
            throw new IOException("Invalid socket name");
        }

        int fd = nativeGetServerSocketFd(socketName);

        if (fd < 0) {
            throw new IOException(
                "Could not retrieve Zygote server socket"
            );
        }

        return fd;
    }
}
