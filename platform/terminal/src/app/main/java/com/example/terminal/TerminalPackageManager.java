package com.example.terminal;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public final class TerminalPackageManager {
    private final File prefix;

    public TerminalPackageManager(String prefix) {
        this.prefix = new File(prefix);
    }

    private void directory(String path) throws IOException {
        File dir = new File(prefix, path);
        if (!dir.isDirectory() && !dir.mkdirs()) {
            throw new IOException("Cannot create " + dir);
        }
    }

    private void file(String path, String content)
            throws IOException {
        File target = new File(prefix, path);
        File parent = target.getParentFile();

        if (parent != null && !parent.isDirectory()
                && !parent.mkdirs()) {
            throw new IOException("Cannot create " + parent);
        }

        if (!target.exists()) {
            try (FileOutputStream out =
                    new FileOutputStream(target)) {
                out.write(content.getBytes("UTF-8"));
            }
        }
    }

    public String execute(String[] args) throws IOException {
        if (args.length < 2) {
            return "pkg: usage: pkg add <name> | pkg install <name>\n";
        }

        String action = args[1];

        if ("add".equals(action) && args.length >= 3) {
            if ("godirs".equals(args[2])) return addGoDirs();
            if ("goenvs".equals(args[2])) return addGoEnvs();
        }

        if ("install".equals(action) && args.length >= 3) {
            if ("openjdk".equals(args[2])) return installOpenJdk();
        }

        return "pkg: unknown package or operation\n";
    }

    private String addGoDirs() throws IOException {
        String[] dirs = {
            "bin", "lib", "lib64", "usr", "env",
            "lib64/go", "lib64/go/src", "lib64/go/pkg",
            "lib64/go/bin", "lib64/go/lib",
            "lib64/go/lib64", "lib64/go/usr",
            "lib64/go/env"
        };

        for (String path : dirs) directory(path);

        file("lib64/go/src/README",
                "Go source workspace\n");
        file("lib64/go/pkg/README",
                "Go package workspace\n");

        return "pkg: Go directories created\n";
    }

    private String addGoEnvs() throws IOException {
        addGoDirs();

        String goRoot = new File(prefix, "lib64/go").getAbsolutePath();
        String goPath = new File(prefix, "lib64/go").getAbsolutePath();
        String goCache = new File(prefix, "tmp/go-build").getAbsolutePath();

        directory("tmp/go-build");

        String settings =
                "GOROOT=" + goRoot + "\n" +
                "GOPATH=" + goPath + "\n" +
                "GOCACHE=" + goCache + "\n" +
                "GOOS=android\n" +
                "GOARCH=arm64\n";

        file("env/go.env", settings);
        file("lib64/go/env", settings);

        return "pkg: Go environment configured in $PREFIX/env/go.env\n";
    }

    private String installOpenJdk() throws IOException {
        directory("var/packages/openjdk");

        file("var/packages/openjdk/installed",
                "package=openjdk\nversion=22\n" +
                "manager=Openjdk22Manager\n");

        return "pkg: Openjdk22Manager registered\n" +
               "pkg: OpenJDK 22 runtime has not been installed\n";
    }
}
