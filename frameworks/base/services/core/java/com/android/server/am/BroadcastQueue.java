package com.android.server.am;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public final class BroadcastQueue {
    private final Queue<BroadcastRecord> queue = new ArrayDeque<>();
    private final List<BroadcastRecord> history = new ArrayList<>();

    public synchronized void enqueue(BroadcastRecord record) {
        if (record == null) {
            throw new IllegalArgumentException("Broadcast is null");
        }

        queue.add(record);
    }

    public synchronized BroadcastRecord dispatchNext() {
        BroadcastRecord record = queue.poll();

        if (record == null) {
            return null;
        }

        record.markDispatching();

        // Delivery to registered receivers is not implemented yet.
        record.markCompleted();
        history.add(record);

        return record;
    }

    public synchronized int getPendingCount() {
        return queue.size();
    }

    public synchronized List<BroadcastRecord> getHistory() {
        return new ArrayList<>(history);
    }

    public synchronized void clear() {
        queue.clear();
        history.clear();
    }
}
