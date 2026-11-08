package com.android.server.am;

import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.Set;

public final class UserController {
    private final Set<Integer> startedUsers = new LinkedHashSet<>();
    private final Set<Integer> unlockedUsers = new LinkedHashSet<>();

    public synchronized boolean startUser(int userId) {
        if (userId < 0) {
            throw new IllegalArgumentException("Invalid user ID");
        }

        return startedUsers.add(userId);
    }

    public synchronized boolean unlockUser(int userId) {
        if (!startedUsers.contains(userId)) {
            return false;
        }

        return unlockedUsers.add(userId);
    }

    public synchronized boolean stopUser(int userId) {
        unlockedUsers.remove(userId);
        return startedUsers.remove(userId);
    }

    public synchronized boolean isUserStarted(int userId) {
        return startedUsers.contains(userId);
    }

    public synchronized boolean isUserUnlocked(int userId) {
        return unlockedUsers.contains(userId);
    }

    public synchronized Set<Integer> getStartedUsers() {
        return Collections.unmodifiableSet(
                new LinkedHashSet<>(startedUsers));
    }
}
