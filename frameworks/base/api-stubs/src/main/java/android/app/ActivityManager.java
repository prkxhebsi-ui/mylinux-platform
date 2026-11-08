package android.app;

import android.content.ComponentName;
import android.content.Context;
import android.os.Debug;

import java.util.List;

public class ActivityManager {
    public static final int IMPORTANCE_FOREGROUND = 100;
    public static final int IMPORTANCE_VISIBLE = 200;
    public static final int IMPORTANCE_SERVICE = 300;
    public static final int IMPORTANCE_BACKGROUND = 400;
    public static final int IMPORTANCE_EMPTY = 500;

    public static class RunningAppProcessInfo {
        public String processName;
        public int pid;
        public int uid;
        public int importance;
        public int importanceReasonCode;
        public int lru;
        public String[] pkgList;

        public RunningAppProcessInfo() {}
    }

    public static class MemoryInfo {
        public long availMem;
        public long totalMem;
        public long threshold;
        public boolean lowMemory;
    }

    public static class RunningServiceInfo {
        public ComponentName service;
        public int pid;
        public int uid;
        public String process;
        public boolean foreground;
        public long activeSince;
        public int clientCount;
    }

    public static class RecentTaskInfo {
        public int id;
        public ComponentName origActivity;
        public ComponentName baseActivity;
    }

    public static class AppTask {
        public RecentTaskInfo getTaskInfo() {
            throw new UnsupportedOperationException("API stub");
        }

        public void finishAndRemoveTask() {
            throw new UnsupportedOperationException("API stub");
        }
    }

    public List<RunningAppProcessInfo> getRunningAppProcesses() {
        throw new UnsupportedOperationException("API stub");
    }

    public List<RunningServiceInfo> getRunningServices(int maxNum) {
        throw new UnsupportedOperationException("API stub");
    }

    public List<AppTask> getAppTasks() {
        throw new UnsupportedOperationException("API stub");
    }

    public void getMemoryInfo(MemoryInfo outInfo) {
        throw new UnsupportedOperationException("API stub");
    }

    public void killBackgroundProcesses(String packageName) {
        throw new UnsupportedOperationException("API stub");
    }

    public static boolean isUserAMonkey() {
        return false;
    }

    public static boolean isRunningInTestHarness() {
        return false;
    }

    public int getMemoryClass() {
        throw new UnsupportedOperationException("API stub");
    }

    public int getLargeMemoryClass() {
        throw new UnsupportedOperationException("API stub");
    }

    public boolean isLowRamDevice() {
        throw new UnsupportedOperationException("API stub");
    }
}
