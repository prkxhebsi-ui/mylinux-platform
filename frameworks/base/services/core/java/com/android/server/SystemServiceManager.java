package com.android.server;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class SystemServiceManager {

    private final Object context;
    private final List<SystemService> services = new ArrayList<>();

    private int currentPhase = -1;
    private boolean started;

    public SystemServiceManager(Object context) {
        if (context == null) {
            throw new IllegalArgumentException("Context cannot be null");
        }

        this.context = context;
    }

    public synchronized <T extends SystemService> T startService(
            Class<T> serviceClass) {

        if (serviceClass == null) {
            throw new IllegalArgumentException("Service class is null");
        }

        try {
            T service = serviceClass
                    .getConstructor(Object.class)
                    .newInstance(context);

            return startService(service);

        } catch (ReflectiveOperationException e) {
            throw new RuntimeException(
                    "Unable to create service: " + serviceClass.getName(), e);
        }
    }

    public synchronized <T extends SystemService> T startService(T service) {

        if (service == null) {
            throw new IllegalArgumentException("Service is null");
        }

        if (started) {
            throw new IllegalStateException(
                    "Cannot start services after boot completion");
        }

        for (SystemService existing : services) {
            if (existing.getClass() == service.getClass()) {
                throw new IllegalStateException(
                        "Service already started: "
                                + service.getClass().getName());
            }
        }

        services.add(service);

        try {
            service.onStart();

            if (currentPhase >= 0) {
                service.dispatchBootPhase(currentPhase);
            }

            return service;

        } catch (RuntimeException | Error e) {
            services.remove(service);
            throw e;
        }
    }

    public synchronized void startBootPhase(int phase) {

        if (phase <= currentPhase) {
            throw new IllegalArgumentException(
                    "Boot phase must be greater than " + currentPhase);
        }

        currentPhase = phase;

        for (SystemService service :
                new ArrayList<>(services)) {
            service.dispatchBootPhase(phase);
        }

        if (phase >= SystemService.PHASE_BOOT_COMPLETED) {
            started = true;
        }
    }

    public synchronized List<SystemService> getServices() {
        return Collections.unmodifiableList(
                new ArrayList<>(services));
    }

    public synchronized int getCurrentPhase() {
        return currentPhase;
    }

    public Object getContext() {
        return context;
    }

    public synchronized boolean isBootCompleted() {
        return started;
    }
}
