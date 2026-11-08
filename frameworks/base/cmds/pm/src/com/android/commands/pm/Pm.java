package com.android.commands.pm;

import java.io.File;

public final class Pm {
    private static final String INSTALLER =
            "com.mylinux.packageinstaller/.InstallActivity";

    private Pm() {}

    public static void main(String[] args) {
        if (args.length == 0) {
            usage();
            return;
        }

        if ("install".equals(args[0])) {
            install(args);
            return;
        }

        if ("help".equals(args[0]) || "--help".equals(args[0])) {
            usage();
            return;
        }

        System.err.println("pm: unknown command: " + args[0]);
        usage();
    }

    private static void install(String[] args) {
        if (args.length != 2) {
            System.err.println("pm: install requires exactly one APK path");
            usage();
            return;
        }

        File apk = new File(args[1]);

        if (!apk.isFile() || !apk.canRead()
                || !apk.getName().toLowerCase().endsWith(".apk")) {
            System.err.println("pm: invalid or unreadable APK: " + args[1]);
            return;
        }

        try {
            Process process = new ProcessBuilder(
                    "/system/bin/am",
                    "start",
                    "-n", INSTALLER,
                    "--es", "apk_path", apk.getAbsolutePath()
            ).inheritIO().start();

            int result = process.waitFor();

            if (result != 0) {
                System.err.println(
                        "pm: unable to launch MyLinux Package Installer");
            }

        } catch (Exception error) {
            System.err.println("pm: installer launch failed: "
                    + error.getMessage());
        }
    }

    private static void usage() {
        System.out.println("MyLinux Package Manager");
        System.out.println("Usage:");
        System.out.println("  pm install <file.apk>");
    }
}
