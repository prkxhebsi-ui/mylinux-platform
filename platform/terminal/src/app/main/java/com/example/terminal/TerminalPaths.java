package com.example.terminal;

public final class TerminalPaths {
    public final String cache;
    public final String files;
    public final String home;
    public final String prefix;

    private TerminalPaths(
            String cache,
            String files,
            String home,
            String prefix) {
        this.cache = cache;
        this.files = files;
        this.home = home;
        this.prefix = prefix;
    }

    public static TerminalPaths initialize(
            android.content.Context context) {

        java.io.File cacheDir = context.getCacheDir();
        java.io.File filesDir = context.getFilesDir();

        java.io.File homeDir =
                new java.io.File(filesDir, "home");

        java.io.File prefixDir =
                new java.io.File(filesDir, "usr");

        create(cacheDir);
        create(homeDir);
        create(prefixDir);

        create(new java.io.File(prefixDir, "bin"));
        create(new java.io.File(prefixDir, "etc"));
        create(new java.io.File(prefixDir, "lib"));
        create(new java.io.File(prefixDir, "libexec"));
        create(new java.io.File(prefixDir, "share"));
        create(new java.io.File(prefixDir, "tmp"));
        create(new java.io.File(prefixDir, "var"));

        return new TerminalPaths(
                cacheDir.getAbsolutePath(),
                filesDir.getAbsolutePath(),
                homeDir.getAbsolutePath(),
                prefixDir.getAbsolutePath());
    }

    private static void create(java.io.File directory) {
        if (!directory.exists() && !directory.mkdirs()) {
            throw new IllegalStateException(
                    "Cannot create: " + directory);
        }
    }
}
