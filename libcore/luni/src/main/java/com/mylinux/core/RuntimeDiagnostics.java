package com.mylinux.core;

import java.util.LinkedHashMap;
import java.util.Map;

/** Produces a snapshot of basic JVM runtime properties. */
public final class RuntimeDiagnostics {
    private RuntimeDiagnostics() {
    }

    public static Map<String, String> snapshot() {
        Map<String, String> result = new LinkedHashMap<>();

        result.put("java.version", RuntimeInfo.javaVersion());
        result.put("java.vm.name", RuntimeInfo.vmName());
        result.put("java.vm.vendor", RuntimeInfo.vmVendor());
        result.put("os.name", RuntimeInfo.osName());
        result.put("os.arch", RuntimeInfo.osArchitecture());
        result.put("runtime.processors",
                Integer.toString(RuntimeInfo.availableProcessors()));
        result.put("runtime.maxMemory",
                Long.toString(RuntimeInfo.maximumMemory()));
        result.put("runtime.totalMemory",
                Long.toString(RuntimeInfo.totalMemory()));
        result.put("runtime.freeMemory",
                Long.toString(RuntimeInfo.freeMemory()));

        return result;
    }
}
