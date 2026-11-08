package com.mylinux.internal.os;

import java.io.IOException;

/**
 * MyLinux integration layer between ART and native Zygote.
 *
 * ART must already be running when this class is used.
 */
public final class ZygoteArtBridge {

    private static final String SOCKET_NAME =
            "zygote_secondary";

    private static int serverSocketFd = -1;

    private ZygoteArtBridge() {
    }

    public static synchronized void initialize()
            throws IOException {

        if (serverSocketFd >= 0) {
            return;
        }

        if (!NativeZygote.isNativeLoaded()) {
            throw new IOException(
                "Native Zygote library is not loaded"
            );
        }

        serverSocketFd =
                NativeZygote.getServerSocketFd(SOCKET_NAME);
    }

    public static synchronized int getServerSocketFd()
            throws IOException {

        if (serverSocketFd < 0) {
            initialize();
        }

        return serverSocketFd;
    }

    public static boolean isArtRunning() {
        return Runtime.getRuntime() != null;
    }
}
