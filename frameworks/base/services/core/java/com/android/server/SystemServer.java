package com.android.server;

public final class SystemServer {

    private static SystemServiceManager serviceManager;
    private static boolean initialized;

    private SystemServer() {
    }

    public static synchronized void initialize(Object context) {

        if (initialized) {
            throw new IllegalStateException(
                    "SystemServer already initialized");
        }

        if (context == null) {
            throw new IllegalArgumentException("Context is null");
        }

        System.out.println("MyLinux SystemServer starting");

        serviceManager = new SystemServiceManager(context);

        SystemServerInitThreadPool.start();

        initialized = true;

        System.out.println("SystemServiceManager initialized");
    }

    public static synchronized SystemServiceManager getServiceManager() {
        if (!initialized) {
            throw new IllegalStateException(
                    "SystemServer has not initialized");
        }

        return serviceManager;
    }

    public static synchronized void startBootPhase(int phase) {
        if (!initialized) {
            throw new IllegalStateException(
                    "SystemServer has not initialized");
        }

        serviceManager.startBootPhase(phase);

        System.out.println("SystemServer boot phase: " + phase);
    }

    public static synchronized void shutdownForTest() {
        if (!initialized) {
            return;
        }

        SystemServerInitThreadPool.shutdown();
        LocalServices.clearServicesForTest();

        serviceManager = null;
        initialized = false;
    }

    public static void main(String[] args) {
        System.out.println(
                "MyLinux SystemServer entry point reached.");

        System.out.println(
                "A real Android boot must provide a system Context "
                + "and initialize Binder before starting framework services.");
    }
}
