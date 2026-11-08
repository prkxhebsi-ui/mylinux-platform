package com.android.server;

/**
 * Base interface for MyLinux system-service prototypes.
 */
public abstract class MyLinuxService {

    private boolean initialized;

    public abstract String getServiceName();

    public void initialize() {
        initialized = true;
    }

    public void shutdown() {
        initialized = false;
    }

    public final boolean isInitialized() {
        return initialized;
    }
}
