package com.example.terminal;

import android.content.Context;
import android.os.Build;
import android.os.Process;
import android.util.Log;

import java.io.File;
import java.util.Arrays;

public final class LLVMLinker32Manager {

    private static final String TAG = "LLVMLinker32";
    private static final String ABI = "armeabi-v7a";

    private final Context context;
    private final File libraryDirectory;
    private final File bootstrapDirectory;

    public LLVMLinker32Manager(Context context) {
        this.context = context.getApplicationContext();
        File files = this.context.getFilesDir();
        File root = new File(new File(files, "usr"), ".root");
        libraryDirectory = new File(root, "system/lib");
        bootstrapDirectory = new File(libraryDirectory, "bootstrap");
    }

    public boolean isSupported() {
        return Arrays.asList(Build.SUPPORTED_ABIS).contains(ABI);
    }

    public boolean isAvailable() {
        return isSupported()
                && libraryDirectory.isDirectory();
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
        Log.i(TAG, "32-bit manager initialized");
        Log.i(TAG, "Supported: " + isSupported());
        Log.i(TAG, "Available: " + isAvailable());
    }
}
