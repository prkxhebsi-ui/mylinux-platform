package com.android.server.am;

import com.android.server.SystemService;

public final class ActivityManagerService extends SystemService {
    private final ProcessList processList = new ProcessList();
    private final BroadcastQueue broadcastQueue = new BroadcastQueue();
    private final ActiveServices activeServices = new ActiveServices();
    private final UserController userController = new UserController();
    private final ContentProviderHelper providerHelper =
            new ContentProviderHelper();

    private volatile boolean running;

    public ActivityManagerService(Object context) {
        super(context);
    }

    @Override
    public void onStart() {
        running = true;
        System.out.println("ActivityManagerService started");
    }

    @Override
    public void onBootPhase(int phase) {
        System.out.println("ActivityManagerService boot phase: " + phase);
    }

    public ProcessRecord startProcess(
            int uid, String processName, String packageName) {

        ensureRunning();
        return processList.startProcess(uid, processName, packageName);
    }

    public boolean killProcess(int pid) {
        ensureRunning();
        return processList.killProcess(pid);
    }

    public void sendBroadcast(
            String action, int userId, Object payload) {

        ensureRunning();
        broadcastQueue.enqueue(
                new BroadcastRecord(action, userId, payload));
    }

    public BroadcastRecord dispatchNextBroadcast() {
        ensureRunning();
        return broadcastQueue.dispatchNext();
    }

    public ProcessList getProcessList() {
        return processList;
    }

    public BroadcastQueue getBroadcastQueue() {
        return broadcastQueue;
    }

    public ActiveServices getActiveServices() {
        return activeServices;
    }

    public UserController getUserController() {
        return userController;
    }

    public ContentProviderHelper getContentProviderHelper() {
        return providerHelper;
    }

    public boolean isRunning() {
        return running;
    }

    private void ensureRunning() {
        if (!running) {
            throw new IllegalStateException(
                    "ActivityManagerService is not running");
        }
    }

    public void shutdownForTest() {
        running = false;
        processList.shutdown();
        activeServices.stopAll();
        broadcastQueue.clear();
    }
}
