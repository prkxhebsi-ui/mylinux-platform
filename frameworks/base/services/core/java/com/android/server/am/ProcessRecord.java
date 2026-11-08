package com.android.server.am;

public final class ProcessRecord {
    public enum State {
        NEW, STARTING, RUNNING, STOPPING, DEAD
    }

    private final int pid;
    private final int uid;
    private final String processName;
    private final String packageName;
    private volatile State state = State.NEW;
    private long startTime;

    public ProcessRecord(int pid, int uid,
                         String processName, String packageName) {
        if (processName == null || packageName == null) {
            throw new IllegalArgumentException("Process identity is required");
        }

        this.pid = pid;
        this.uid = uid;
        this.processName = processName;
        this.packageName = packageName;
    }

    public synchronized void start() {
        if (state != State.NEW) {
            throw new IllegalStateException("Process already started");
        }

        state = State.STARTING;
        startTime = System.currentTimeMillis();
        state = State.RUNNING;
    }

    public synchronized void stop() {
        if (state == State.DEAD) return;
        state = State.STOPPING;
        state = State.DEAD;
    }

    public int getPid() { return pid; }
    public int getUid() { return uid; }
    public String getProcessName() { return processName; }
    public String getPackageName() { return packageName; }
    public State getState() { return state; }
    public long getStartTime() { return startTime; }

    public boolean isAlive() {
        return state == State.RUNNING;
    }
}
