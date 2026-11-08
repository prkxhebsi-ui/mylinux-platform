package com.android.server.pm;

import java.util.LinkedHashMap;
import java.util.Map;

public final class PackageSetting {
    private final String packageName;
    private final String apkPath;
    private final long firstInstallTime;
    private long lastUpdateTime;

    private final Map<Integer, PackageUserState> userStates =
            new LinkedHashMap<>();

    public PackageSetting(String packageName, String apkPath) {
        if (packageName == null || packageName.trim().isEmpty()) {
            throw new IllegalArgumentException("Invalid package name");
        }

        this.packageName = packageName;
        this.apkPath = apkPath;
        this.firstInstallTime = System.currentTimeMillis();
        this.lastUpdateTime = firstInstallTime;
    }

    public synchronized PackageUserState getUserState(int userId) {
        PackageUserState state = userStates.get(userId);

        if (state == null) {
            state = new PackageUserState(userId);
            userStates.put(userId, state);
        }

        return state;
    }

    public synchronized void updateTime() {
        lastUpdateTime = System.currentTimeMillis();
    }

    public String getPackageName() { return packageName; }
    public String getApkPath() { return apkPath; }
    public long getFirstInstallTime() { return firstInstallTime; }
    public long getLastUpdateTime() { return lastUpdateTime; }
}
