package com.example.terminal;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public final class TerminalSystemLayout {

    private TerminalSystemLayout() {
    }

    private static void directory(File file) throws IOException {
        if (!file.isDirectory() &&
                !file.mkdirs()) {
            throw new IOException("Cannot create " + file);
        }
    }

    private static void command(File bin, String name)
            throws IOException {
        File file = new File(bin, name);

        if (!file.exists()) {
            try (FileOutputStream out = new FileOutputStream(file)) {
                String content =
                        "MYLINUX-JAVA-COMMAND\n" +
                        "name=" + name + "\n" +
                        "provider=TerminalCommandRegistry\n";

                out.write(content.getBytes("UTF-8"));
            }
        }
    }

    public static void create(File virtualRoot)
            throws IOException {

        File system = new File(virtualRoot, "system");

        File bin = new File(system, "bin");
        File lib = new File(system, "lib");
        File lib64 = new File(system, "lib64");

        directory(system);
        directory(bin);
        directory(lib);
        directory(new File(lib, "hw"));
        directory(new File(lib, "mylinux"));

        directory(lib64);
        directory(new File(lib64, "bootstrap"));

        String[] commands = {
            "mkdir",
            "tset",
            "uset",
            "set",
            "export",
            "mkpath",
            "linker64",
            "linker"
        };

        for (String name : commands) {
            command(bin, name);
        }
    }
}
