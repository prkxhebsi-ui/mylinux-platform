package com.example.terminal;

public final class TerminalFilesystem {
    private final String prefix;
    private final java.io.File root;

    public TerminalFilesystem(TerminalEnvironment env) {
        prefix = env.PREFIX;
        root = new java.io.File(prefix, ".root");

        if (!root.exists() && !root.mkdirs()) {
            throw new IllegalStateException("Cannot create virtual root");
        }
    }

    public java.io.File resolve(String path,
                                java.io.File workingDirectory) {
        if (path == null || path.length() == 0) {
            return workingDirectory;
        }

        String normalized = path.replace('\\', '/');

        if (normalized.contains("/.root") ||
            normalized.equals(".root") ||
            normalized.startsWith(".root/")) {
            return new java.io.File("/__mylinux_hidden_path__");
        }

        java.io.File result;

        if (normalized.startsWith("/")) {
            result = new java.io.File(root, normalized.substring(1));
        } else {
            result = new java.io.File(workingDirectory, normalized);
        }

        try {
            String base = root.getCanonicalPath();
            String target = result.getCanonicalPath();

            if (target.equals(base) || target.startsWith(base + "/")) {
                return result;
            }

            if (normalized.startsWith("/")) {
                return new java.io.File("/__mylinux_hidden_path__");
            }

            return result;
        } catch (java.io.IOException e) {
            return new java.io.File("/__mylinux_hidden_path__");
        }
    }

    public String realpath(String path,
                           java.io.File workingDirectory) {
        java.io.File file = resolve(path, workingDirectory);

        try {
            String base = root.getCanonicalPath();
            String target = file.getCanonicalPath();

            if (target.equals(base)) return "/";
            if (target.startsWith(base + "/")) {
                return target.substring(base.length());
            }
            return file.getAbsolutePath();
        } catch (java.io.IOException e) {
            return "realpath: cannot resolve path";
        }
    }

    public java.io.File getRoot() {
        return root;
    }
}
