package com.android.server.pm;

import com.android.server.SystemService;
import java.util.LinkedHashSet;
import java.util.Set;

public final class UserManagerService extends SystemService {
    private final Set<Integer> users = new LinkedHashSet<>();

    public UserManagerService(Object context) {
        super(context);
        users.add(0);
    }

    @Override
    public void onStart() {
        System.out.println("UserManagerService started");
    }

    public synchronized boolean createUser(int userId) {
        if (userId < 0) {
            throw new IllegalArgumentException("Invalid user ID");
        }
        return users.add(userId);
    }

    public synchronized boolean removeUser(int userId) {
        if (userId == 0) return false;
        return users.remove(userId);
    }

    public synchronized boolean exists(int userId) {
        return users.contains(userId);
    }

    public synchronized Set<Integer> getUsers() {
        return new LinkedHashSet<>(users);
    }
}
