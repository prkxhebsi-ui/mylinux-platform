package com.example.terminal;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Handler;
import android.os.Looper;
import android.system.Os;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public final class TerminalFirstRun {

    private static final String PREFS = "terminal_setup";
    private static final String COMPLETE = "directories_created";

    public interface Listener {
        void onCreatingDirectories();
        void onDirectory(String path, boolean created);
        void onFinished(boolean firstRun);
        void onError(String path);
    }

    private TerminalFirstRun() {
    }

    private static void makeDirectory(File directory)
            throws IOException {
        if (!directory.isDirectory() &&
                !directory.mkdirs()) {
            throw new IOException("Cannot create " + directory);
        }
    }

    private static void writeFile(File file, String content)
            throws IOException {
        try (FileOutputStream output = new FileOutputStream(file)) {
            output.write(content.getBytes("UTF-8"));
        }
    }

    private static void createDevice(
            File dev, String name, String type)
            throws IOException {
        writeFile(
                new File(dev, name),
                "virtual-device-type=" + type + "\n"
        );
    }

    private static void createFilesystem(File files)
            throws IOException {

        File usr = new File(files, "usr");
        File root = new File(usr, ".root");

        File dev = new File(root, "dev");
        File run = new File(root, "run");
        File lock = new File(run, "lock");
        File systemd = new File(run, "systemd");
        File sv = new File(root, "sv");

        makeDirectory(root);
        makeDirectory(dev);
        makeDirectory(run);
        makeDirectory(lock);
        makeDirectory(systemd);
        makeDirectory(sv);

        // Sticky directory permissions: 01777.
        Os.chmod(lock.getAbsolutePath(), 01777);

        // Virtual device entries.
        createDevice(dev, "root", "block");
        createDevice(dev, "zero", "character");
        createDevice(dev, "null", "character");
        createDevice(dev, "binder", "character");

        createDevice(dev, "loop", "loop");
        createDevice(dev, "loop2", "loop");
        createDevice(dev, "loop3", "loop");
        createDevice(dev, "loop4", "loop");

        createDevice(dev, "kvm", "character");

        // Virtual processor and graphics information.
        writeFile(
                new File(dev, "arm:varient"),
                "Cortex-A53\n"
        );

        writeFile(
                new File(dev, "arm64:varient"),
                "Adreno\n"
        );

        // Container identification.
        writeFile(
                new File(systemd, "container"),
                "docker\n"
        );
    }

    public static void runIfNeeded(
            Context context, Listener listener) {

        Context app = context.getApplicationContext();

        SharedPreferences prefs =
                app.getSharedPreferences(PREFS, Context.MODE_PRIVATE);

        Handler main = new Handler(Looper.getMainLooper());

        new Thread(() -> {
            boolean firstRun =
                    !prefs.getBoolean(COMPLETE, false);

            if (firstRun) {
                main.post(listener::onCreatingDirectories);
            }

            File files = app.getFilesDir();
            File usr = new File(files, "usr");

            File[] directories = {
                app.getCacheDir(),
                files,
                new File(files, "home"),
                usr,
                new File(usr, "bin"),
                new File(usr, "etc"),
                new File(usr, "lib"),
                new File(usr, "libexec"),
                new File(usr, "share"),
                new File(usr, "tmp"),
                new File(usr, "var"),
                new File(usr, ".root"),
                new File(usr, ".root/sv")
            };

            String[] names = {
                "/cache",
                "/files",
                "/home",
                "/usr",
                "/usr/bin",
                "/usr/etc",
                "/usr/lib",
                "/usr/libexec",
                "/usr/share",
                "/usr/tmp",
                "/usr/var",
                null,
                "/sv"
            };

            boolean success = true;

            try {
                for (int i = 0; i < directories.length; i++) {
                    File directory = directories[i];
                    boolean existed = directory.isDirectory();

                    makeDirectory(directory);

                    if (firstRun && names[i] != null) {
                        String path = names[i];
                        main.post(() ->
                                listener.onDirectory(path, !existed));
                    }
                }

                TerminalSystemLayout.create(
                        new File(new File(files, "usr"), ".root")
                );

                if (firstRun) {
                    prefs.edit()
                            .putBoolean(COMPLETE, true)
                            .apply();
                }

            } catch (Exception e) {
                success = false;
                main.post(() -> listener.onError("/"));
            }

            boolean result = success;
            main.post(() -> listener.onFinished(result));

        }, "terminal-first-run").start();
    }
}
