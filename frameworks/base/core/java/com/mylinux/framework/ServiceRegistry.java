package com.mylinux.framework;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * Registry for MyLinux framework services.
 */
public final class ServiceRegistry {
    private static final Map<String, SystemService> SERVICES =
        new HashMap<>();

    private ServiceRegistry() {}

    public static synchronized void register(SystemService service) {
        if (service == null) {
            throw new IllegalArgumentException("Service is null");
        }

        String name = service.getServiceName();

        if (SERVICES.containsKey(name)) {
            throw new IllegalStateException(
                "Service already registered: " + name
            );
        }

        SERVICES.put(name, service);
    }

    public static synchronized SystemService get(String name) {
        return SERVICES.get(name);
    }

    public static synchronized Map<String, SystemService> getAll() {
        return Collections.unmodifiableMap(
            new HashMap<>(SERVICES)
        );
    }
}
