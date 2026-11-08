package com.example.terminal;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.LinkOption;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPOutputStream;

public final class IConfigManger {

    private final File root;
    private final File marker;
    private final File owners;

    private boolean sessionStarted;
    private String startupMessage = "";

    private static final String FSTAB =
            "debugfs /d debugfs defaults 0 0\n" +
            "procfs /proc proc defaults 0 0\n" +
            "tmpfs /run tmpfs defaults 0 0\n" +
            "devtmpfs /dev devtmpfs defaults 0 0\n" +
            "sysfs /sys sysfs defaults 0 0\n";

    public IConfigManger(File virtualRoot) {
        if (virtualRoot == null) {
            throw new IllegalArgumentException("Virtual root required");
        }

        root = virtualRoot;
        marker = new File(root.getParentFile(),
                ".mylinux-config-registered");
        owners = new File(root.getParentFile(),
                ".mylinux-owner-map");
    }

    private File path(String name) {
        return new File(root, name);
    }

    private void directory(File file) throws IOException {
        if (!file.isDirectory() && !file.mkdirs()) {
            throw new IOException("Cannot create " + file);
        }
    }

    private void write(File file, String content)
            throws IOException {
        directory(file.getParentFile());

        try (FileOutputStream out = new FileOutputStream(file)) {
            out.write(content.getBytes("UTF-8"));
        }
    }

    private void symlink(File link, String target)
            throws IOException {
        directory(link.getParentFile());

        Path linkPath = link.toPath();

        if (Files.exists(linkPath, LinkOption.NOFOLLOW_LINKS)) {
            if (Files.isSymbolicLink(linkPath)) {
                Files.delete(linkPath);
            } else {
                throw new IOException(
                        "Cannot replace non-symlink: " + link);
            }
        }

        Files.createSymbolicLink(
                linkPath,
                Paths.get(target)
        );
    }

    private void deleteTree(File file) throws IOException {
        Path p = file.toPath();

        if (!Files.exists(p, LinkOption.NOFOLLOW_LINKS)) {
            return;
        }

        if (Files.isSymbolicLink(p) || !file.isDirectory()) {
            Files.deleteIfExists(p);
            return;
        }

        File[] children = file.listFiles();

        if (children != null) {
            for (File child : children) {
                deleteTree(child);
            }
        }

        Files.deleteIfExists(p);
    }

    private void createConfigGzip() throws IOException {
        File output = path("proc/config.gz");

        directory(output.getParentFile());

        String config =
                "CONFIG_ANDROID=y\n" +
                "CONFIG_PROC_FS=y\n" +
                "CONFIG_SYSFS=y\n" +
                "CONFIG_TMPFS=y\n" +
                "CONFIG_DEVTMPFS=y\n" +
                "CONFIG_DEBUG_FS=y\n";

        try (GZIPOutputStream gzip =
                     new GZIPOutputStream(
                             new FileOutputStream(output))) {
            gzip.write(config.getBytes("UTF-8"));
        }
    }

    private void createFstab() throws IOException {
        write(path("etc/fstab.gto"), FSTAB);
    }

    private void createPersistentSdcard() throws IOException {
        File target = path("storage/self/primary");
        directory(target);

        File link = path("sdcard");

        if (!Files.exists(link.toPath(),
                LinkOption.NOFOLLOW_LINKS)) {
            symlink(link, "storage/self/primary");
        }
    }

    private void createSessionFilesystem() throws IOException {
        directory(path("dev"));
        directory(path("proc"));
        directory(path("sys"));
        directory(path("run"));

        directory(path("proc/213880"));
        directory(path("proc/debug/info"));

        write(path("proc/213880/mounts"), FSTAB);

        write(path("proc/debug/info/README"),
                "MyLinux virtual debugfs\n");

        symlink(path("proc/self"), "213880");
        symlink(path("proc/mounts"), "self/mounts");
        symlink(path("d"), "proc/debug/info");

        createConfigGzip();
        createFstab();
    }

    public synchronized String startSession()
            throws IOException {

        if (sessionStarted) return "";

        directory(root);

        // Remove stale temporary trees from an unclean exit.
        deleteTree(path("dev"));
        deleteTree(path("proc"));
        deleteTree(path("sys"));
        deleteTree(path("run"));
        deleteTree(path("d"));

        createPersistentSdcard();
        createSessionFilesystem();

        if (!marker.exists()) {
            startupMessage =
                    "registering android specific Android UIDs/GIDs\n";

            try (FileOutputStream out =
                         new FileOutputStream(marker)) {
                out.write("registered\n".getBytes("UTF-8"));
            }
        }

        sessionStarted = true;

        return startupMessage;
    }

    public synchronized void endSession()
            throws IOException {

        if (!sessionStarted) return;

        deleteTree(path("dev"));
        deleteTree(path("proc"));
        deleteTree(path("sys"));
        deleteTree(path("run"));
        deleteTree(path("d"));

        sessionStarted = false;
    }

    public String filesystem(String name) {
        if (name == null || name.isEmpty()) {
            return "filesystem: missing path\n";
        }

        String p = name.startsWith("/") ? name : "/" + name;

        switch (p) {
            case "/dev":
                return "devtmpfs\n";
            case "/proc":
                return "procfs\n";
            case "/sys":
                return "sysfs\n";
            case "/d":
                return "debugfs\n";
            case "/run":
                return "tmpfs\n";
            default:
                return "filesystem: unknown path: " + p + "\n";
        }
    }

    public synchronized void recordRootDirectory(File directory)
            throws IOException {

        if (directory == null || !directory.isDirectory()) {
            return;
        }

        String rootPath = root.getCanonicalPath();
        String parent = directory.getCanonicalFile()
                .getParentFile().getCanonicalPath();

        if (!rootPath.equals(parent)) return;

        String entry = "/" + directory.getName() + " root:root\n";

        try (FileWriter writer = new FileWriter(owners, true)) {
            writer.write(entry);
        }
    }

    public File getRoot() {
        return root;
    }
}
