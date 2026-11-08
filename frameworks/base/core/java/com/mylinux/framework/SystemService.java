package com.mylinux.framework;

/**
 * Base class for MyLinux framework services.
 */
public abstract class SystemService {
    private final String serviceName;
    private boolean started;

    protected SystemService(String serviceName) {
        if (serviceName == null || serviceName.isEmpty()) {
            throw new IllegalArgumentException("Invalid service name");
        }

        this.serviceName = serviceName;
    }

    public final String getServiceName() {
        return serviceName;
    }

    public final boolean isStarted() {
        return started;
    }

    public final synchronized void start() {
        if (started) {
            return;
        }

        onStart();
        started = true;
    }

    protected abstract void onStart();
}
