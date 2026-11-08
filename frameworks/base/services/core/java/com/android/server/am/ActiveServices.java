package com.android.server.am;

import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;

public final class ActiveServices {
    public static final class ServiceRecord {
        private final String component;
        private final int userId;
        private final long createdAt;
        private boolean running;

        ServiceRecord(String component, int userId) {
            this.component = component;
            this.userId = userId;
            this.createdAt = System.currentTimeMillis();
            this.running = true;
        }

        public String getComponent() { return component; }
        public int getUserId() { return userId; }
        public long getCreatedAt() { return createdAt; }
        public boolean isRunning() { return running; }
    }

    private final Map<String, ServiceRecord> services =
            new LinkedHashMap<>();

    private String key(String component, int userId) {
        return userId + ":" + component;
    }

    public synchronized ServiceRecord startService(
            String component, int userId) {

        if (component == null || component.trim().isEmpty()) {
            throw new IllegalArgumentException("Invalid component");
        }

        String key = key(component, userId);
        ServiceRecord record = services.get(key);

        if (record == null) {
            record = new ServiceRecord(component, userId);
            services.put(key, record);
        }

        return record;
    }

    public synchronized boolean stopService(
            String component, int userId) {

        ServiceRecord record = services.remove(key(component, userId));

        if (record == null) return false;

        record.running = false;
        return true;
    }

    public synchronized Map<String, ServiceRecord> getServices() {
        return Collections.unmodifiableMap(
                new LinkedHashMap<>(services));
    }

    public synchronized void stopAll() {
        for (ServiceRecord record : services.values()) {
            record.running = false;
        }

        services.clear();
    }
}
