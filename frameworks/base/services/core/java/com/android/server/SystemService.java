package com.android.server;

public abstract class SystemService {

    public static final int PHASE_WAIT_FOR_DEFAULT_DISPLAY = 100;
    public static final int PHASE_SYSTEM_SERVICES_READY = 500;
    public static final int PHASE_DEVICE_SPECIFIC_SERVICES_READY = 520;
    public static final int PHASE_ACTIVITY_MANAGER_READY = 550;
    public static final int PHASE_THIRD_PARTY_APPS_CAN_START = 600;
    public static final int PHASE_BOOT_COMPLETED = 1000;

    private final Object context;
    private int currentPhase = -1;

    public SystemService(Object context) {
        if (context == null) {
            throw new IllegalArgumentException("Context cannot be null");
        }
        this.context = context;
    }

    public final Object getContext() {
        return context;
    }

    public abstract void onStart();

    public void onBootPhase(int phase) {
    }

    public void onStartUser(int userId) {
    }

    public void onUnlockUser(int userId) {
    }

    public void onStopUser(int userId) {
    }

    final void dispatchBootPhase(int phase) {
        if (phase <= currentPhase) {
            throw new IllegalArgumentException("Boot phases must increase");
        }

        currentPhase = phase;
        onBootPhase(phase);
    }

    public final int getCurrentPhase() {
        return currentPhase;
    }
}
