package com.android.server.am;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public final class ProcessList {
    private final Map<Integer, ProcessRecord> processes =
            new LinkedHashMap<>();

    private final AtomicInteger nextPid = new AtomicInteger(10000);

    public synchronized ProcessRecord startProcess(
            int uid, String processName, String packageName) {

        for (ProcessRecord process : processes.values()) {
            if (process.isAlive()
                    && process.getProcessName().equals(processName)) {
                return process;
            }
        }

        int pid = nextPid.getAndIncrement();

        ProcessRecord record =
                new ProcessRecord(pid, uid, processName, packageName);

        record.start();
        processes.put(pid, record);

        return record;
    }

    public synchronized boolean killProcess(int pid) {
        ProcessRecord record = processes.get(pid);

        if (record == null || !record.isAlive()) {
            return false;
        }

        record.stop();
        processes.remove(pid);
        return true;
    }

    public synchronized ProcessRecord getProcess(int pid) {
        return processes.get(pid);
    }

    public synchronized Collection<ProcessRecord> getProcesses() {
        return new ArrayList<>(processes.values());
    }

    public synchronized int getProcessCount() {
        return processes.size();
    }

    public synchronized void removeDeadProcesses() {
        processes.values().removeIf(
                process -> !process.isAlive());
    }

    public synchronized void shutdown() {
        for (ProcessRecord process : processes.values()) {
            process.stop();
        }

        processes.clear();
    }
}
