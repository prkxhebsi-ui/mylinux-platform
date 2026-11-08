package com.example.terminal;

import android.content.Context;
import android.os.Build;
import android.os.Process;
import android.util.Log;

import java.io.File;
import java.util.Arrays;

public final class LLVMLinker64Manager {

    private static final String TAG = "LLVMLinker64";
    private static final String ABI = "arm64-v8a";

    private final Context context;
    private final File libraryDirectory;
    private final File bootstrapDirectory;

    public LLVMLinker64Manager(Context context) {
        this.context = context.getApplicationContext();
        File files = this.context.getFilesDir();
        File root = new File(new File(files, "usr"), ".root");
        libraryDirectory = new File(root, "system/lib64");
        bootstrapDirectory = new File(libraryDirectory, "bootstrap");
    }

    public boolean isSupported() {
        return Process.is64Bit()
                && Arrays.asList(Build.SUPPORTED_ABIS).contains(ABI);
    }

    public boolean isAvailable() {
        return isSupported()
                && libraryDirectory.isDirectory()
                && bootstrapDirectory.isDirectory();
    }

    public File getLibraryDirectory() {
        return libraryDirectory;
    }

    public File getBootstrapDirectory() {
        return bootstrapDirectory;
    }

    public String getArchitecture() {
        return ABI;
    }

    public void logStatus() {
        Log.i(TAG, "64-bit manager initialized");
        Log.i(TAG, "Supported: " + isSupported());
        Log.i(TAG, "Available: " + isAvailable());
    }
}
