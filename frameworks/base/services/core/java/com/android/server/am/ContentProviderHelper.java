package com.android.server.am;

import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;

public final class ContentProviderHelper {
    public static final class ProviderRecord {
        private final String authority;
        private final String packageName;
        private final int uid;

        ProviderRecord(String authority, String packageName, int uid) {
            this.authority = authority;
            this.packageName = packageName;
            this.uid = uid;
        }

        public String getAuthority() { return authority; }
        public String getPackageName() { return packageName; }
        public int getUid() { return uid; }
    }

    private final Map<String, ProviderRecord> providers =
            new LinkedHashMap<>();

    public synchronized void registerProvider(
            String authority, String packageName, int uid) {

        if (authority == null || authority.trim().isEmpty()
                || packageName == null || packageName.trim().isEmpty()) {
            throw new IllegalArgumentException("Invalid provider identity");
        }

        ProviderRecord record =
                new ProviderRecord(authority, packageName, uid);

        ProviderRecord previous = providers.putIfAbsent(authority, record);

        if (previous != null) {
            throw new IllegalStateException(
                    "Provider authority already registered: " + authority);
        }
    }

    public synchronized ProviderRecord getProvider(String authority) {
        return providers.get(authority);
    }

    public synchronized boolean removeProvider(String authority) {
        return providers.remove(authority) != null;
    }

    public synchronized Map<String, ProviderRecord> getProviders() {
        return Collections.unmodifiableMap(
                new LinkedHashMap<>(providers));
    }
}
