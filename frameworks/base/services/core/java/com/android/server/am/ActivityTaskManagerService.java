package com.android.server.am;

import com.android.server.SystemService;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public final class ActivityTaskManagerService extends SystemService {
    public static final class TaskRecord {
        private final int taskId;
        private final String packageName;
        private final int userId;
        private final long createdAt;

        TaskRecord(int taskId, String packageName, int userId) {
            this.taskId = taskId;
            this.packageName = packageName;
            this.userId = userId;
            this.createdAt = System.currentTimeMillis();
        }

        public int getTaskId() { return taskId; }
        public String getPackageName() { return packageName; }
        public int getUserId() { return userId; }
        public long getCreatedAt() { return createdAt; }
    }

    private final AtomicInteger nextTaskId = new AtomicInteger(1);
    private final Map<Integer, TaskRecord> tasks =
            new LinkedHashMap<>();

    public ActivityTaskManagerService(Object context) {
        super(context);
    }

    @Override
    public void onStart() {
        System.out.println("ActivityTaskManagerService started");
    }

    public synchronized TaskRecord createTask(
            String packageName, int userId) {

        if (packageName == null || packageName.trim().isEmpty()) {
            throw new IllegalArgumentException("Package name is empty");
        }

        int id = nextTaskId.getAndIncrement();

        TaskRecord task = new TaskRecord(id, packageName, userId);
        tasks.put(id, task);

        return task;
    }

    public synchronized boolean removeTask(int taskId) {
        return tasks.remove(taskId) != null;
    }

    public synchronized TaskRecord getTask(int taskId) {
        return tasks.get(taskId);
    }

    public synchronized List<TaskRecord> getTasks() {
        return Collections.unmodifiableList(
                new ArrayList<>(tasks.values()));
    }
}
