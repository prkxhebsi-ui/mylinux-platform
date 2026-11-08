package com.android.server.pm;

import com.android.server.SystemService;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public final class PermissionManagerService extends SystemService {
    private final Map<Integer, Set<String>> grants = new HashMap<>();

    public PermissionManagerService(Object context) {
        super(context);
    }

    @Override
    public void onStart() {
        System.out.println("PermissionManagerService started");
    }

    public synchronized void grantPermission(int uid, String permission) {
        if (permission == null || permission.trim().isEmpty()) {
            throw new IllegalArgumentException("Invalid permission");
        }

        grants.computeIfAbsent(uid, key -> new HashSet<>()).add(permission);
    }

    public synchronized void revokePermission(int uid, String permission) {
        Set<String> permissions = grants.get(uid);
        if (permissions != null) {
            permissions.remove(permission);
        }
    }

    public synchronized boolean hasPermission(int uid, String permission) {
        Set<String> permissions = grants.get(uid);
        return permissions != null && permissions.contains(permission);
    }
}
