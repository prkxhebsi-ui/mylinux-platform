package com.android.server.am;

public final class BroadcastRecord {
    public enum State {
        PENDING, DISPATCHING, COMPLETED, FAILED
    }

    private final String action;
    private final int userId;
    private final Object payload;
    private final long enqueueTime;

    private volatile State state = State.PENDING;

    public BroadcastRecord(String action, int userId, Object payload) {
        if (action == null || action.trim().isEmpty()) {
            throw new IllegalArgumentException("Broadcast action is empty");
        }

        this.action = action;
        this.userId = userId;
        this.payload = payload;
        this.enqueueTime = System.currentTimeMillis();
    }

    public void markDispatching() {
        state = State.DISPATCHING;
    }

    public void markCompleted() {
        state = State.COMPLETED;
    }

    public void markFailed() {
        state = State.FAILED;
    }

    public String getAction() { return action; }
    public int getUserId() { return userId; }
    public Object getPayload() { return payload; }
    public long getEnqueueTime() { return enqueueTime; }
    public State getState() { return state; }
}
