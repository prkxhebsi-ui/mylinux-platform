package com.android.server;

import java.util.concurrent.ConcurrentHashMap;
import java.util.Map;

public final class LocalServices {

    private static final Map<Class<?>, Object> SERVICES =
            new ConcurrentHashMap<>();

    private LocalServices() {
    }

    public static <T> void addService(Class<T> type, T service) {
        if (type == null || service == null) {
            throw new IllegalArgumentException("Null service registration");
        }

        Object previous = SERVICES.putIfAbsent(type, service);

        if (previous != null) {
            throw new IllegalStateException(
                    "Service already registered: " + type.getName());
        }
    }

    public static <T> T getService(Class<T> type) {
        Object service = SERVICES.get(type);

        if (service == null) {
            return null;
        }

        return type.cast(service);
    }

    public static <T> void removeServiceForTest(Class<T> type) {
        SERVICES.remove(type);
    }

    public static void clearServicesForTest() {
        SERVICES.clear();
    }
}
