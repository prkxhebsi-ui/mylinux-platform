package com.example.terminal;

public final class TerminalProcess {
    private final TerminalEnvironment env;
    private final TerminalFilesystem filesystem;
    private final IConfigManger configManager;
    private java.io.File currentDirectory;
    private String startupMessage = "";
    private String startupError = "";

    public TerminalProcess(TerminalEnvironment environment) {
        if (environment == null) {
            throw new IllegalArgumentException("Environment required");
        }

        env = environment;
        filesystem = new TerminalFilesystem(env);
        configManager = new IConfigManger(filesystem.getRoot());
        currentDirectory = new java.io.File(env.HOME);

        try {
            startupMessage = configManager.startSession();
        } catch (java.io.IOException e) {
            startupError = "MyLinux filesystem startup: " +
                    e.getMessage() + "\n";
        }
    }

    public String execute(String line) {
        if (line == null || line.trim().isEmpty()) return "";

        String[] args = line.trim().split("\\s+");
        String command = args[0];

        try {
            switch (command) {
                case "filesystem":
                    return filesystemInfo(args);
                case "mount":
                    return mount();
                case "cat":
                    return cat(args);
                case "cd":
                    return cd(args);
                case "ls":
                    return ls(args);
                case "tree":
                    return tree(args);
                case "mkdir":
                    return mkdir(args, false);
                case "mkpath":
                    return mkdir(args, true);
                case "rmdir":
                    return rmdir(args);
                case "mktemp":
                    return mktemp();
                case "gzip":
                    return gzip(args);
                case "gunzip":
                    return gunzip(args);
                case "zcat":
                    return zcat(args);
                case "pwd":
                case "realpath":
                    return realpath(args);
                default:
                    return external(args);
            }
        } catch (Exception e) {
            return command + ": " + e.getMessage() + "\n";
        }
    }

    private String filesystemInfo(String[] args) {
        if (args.length < 2) {
            return "filesystem: missing path\n";
        }
        return configManager.filesystem(args[1]);
    }

    // Show the current virtual mount table.
    private String mount() throws Exception {
        return cat(new String[] { "cat", "/proc/mounts" });
    }

    // Read one or more files from the virtual filesystem.
    private String cat(String[] args) throws Exception {
        if (args.length < 2) {
            return "cat: missing file operand\n";
        }

        StringBuilder output = new StringBuilder();

        for (int i = 1; i < args.length; i++) {
            java.io.File file = resolve(args[i]);

            try (java.io.FileInputStream input =
                     new java.io.FileInputStream(file)) {
                output.append(new String(
                        input.readAllBytes(), "UTF-8"));
            } catch (java.io.IOException e) {
                return "cat: " + args[i] + ": " +
                        e.getMessage() + "\n";
            }
        }

        return output.toString();
    }

    private java.io.File resolve(String path) {
        return filesystem.resolve(path, currentDirectory);
    }

    private String cd(String[] args) {
        String target = args.length > 1 ? args[1] : env.HOME;
        java.io.File dir = resolve(target);

        if (!dir.isDirectory()) return "cd: not a directory\n";

        currentDirectory = dir;
        return "";
    }

    private String ls(String[] args) {
        java.io.File dir = resolve(args.length > 1 ? args[1] : ".");
        String[] names = dir.list();

        if (names == null) return "ls: cannot access directory\n";

        StringBuilder out = new StringBuilder();
        for (String name : names) {
            out.append(name).append('\n');
        }
        return out.toString();
    }

    private String tree(String[] args) {
        java.io.File root = resolve(args.length > 1 ? args[1] : ".");
        StringBuilder out = new StringBuilder();
        out.append(root.getName()).append('\n');
        appendTree(root, "", out);
        return out.toString();
    }

    private void appendTree(java.io.File dir, String prefix,
                            StringBuilder out) {
        java.io.File[] children = dir.listFiles();
        if (children == null) return;

        for (int i = 0; i < children.length; i++) {
            java.io.File child = children[i];
            boolean last = i == children.length - 1;

            out.append(prefix)
               .append(last ? "└── " : "├── ")
               .append(child.getName())
               .append('\n');

            if (child.isDirectory()) {
                appendTree(child, prefix + (last ? "    " : "│   "), out);
            }
        }
    }

    private String mkdir(String[] args, boolean parents) {
        if (args.length < 2) return "mkdir: missing operand\n";

        java.io.File dir = resolve(args[1]);
        boolean ok = parents ? dir.mkdirs() : dir.mkdir();

        if (!ok && !dir.isDirectory()) {
            return "mkdir: cannot create directory\n";
        }

        if (dir.isDirectory()) {
            configManager.recordRootDirectory(dir);
        }

        return "";
    }

    private String rmdir(String[] args) {
        if (args.length < 2) return "rmdir: missing operand\n";

        java.io.File dir = resolve(args[1]);
        if (!dir.isDirectory()) return "rmdir: not a directory\n";

        if (!dir.delete()) return "rmdir: directory not empty or inaccessible\n";
        return "";
    }

    private String mktemp() throws Exception {
        java.io.File dir = new java.io.File(env.TMPDIR);
        dir.mkdirs();

        java.io.File temp = java.io.File.createTempFile(
                "tmp.", "", dir);

        return temp.getAbsolutePath() + "\n";
    }

    private String gzip(String[] args) throws Exception {
        if (args.length < 2) return "gzip: missing file\n";

        java.io.File input = resolve(args[1]);
        java.io.File output = new java.io.File(input.getPath() + ".gz");

        try (java.io.FileInputStream in =
                 new java.io.FileInputStream(input);
             java.util.zip.GZIPOutputStream out =
                 new java.util.zip.GZIPOutputStream(
                     new java.io.FileOutputStream(output))) {
            in.transferTo(out);
        }
        return "";
    }

    private String gunzip(String[] args) throws Exception {
        if (args.length < 2) return "gunzip: missing file\n";

        java.io.File input = resolve(args[1]);
        String name = input.getName();
        if (!name.endsWith(".gz")) {
            return "gunzip: filename must end in .gz\n";
        }

        java.io.File output = new java.io.File(
                input.getParentFile(),
                name.substring(0, name.length() - 3));

        try (java.util.zip.GZIPInputStream in =
                 new java.util.zip.GZIPInputStream(
                     new java.io.FileInputStream(input));
             java.io.FileOutputStream out =
                 new java.io.FileOutputStream(output)) {
            in.transferTo(out);
        }
        return "";
    }

    private String zcat(String[] args) throws Exception {
        if (args.length < 2) return "zcat: missing file\n";

        java.io.File input = resolve(args[1]);
        java.io.ByteArrayOutputStream out =
                new java.io.ByteArrayOutputStream();

        try (java.util.zip.GZIPInputStream in =
                 new java.util.zip.GZIPInputStream(
                     new java.io.FileInputStream(input))) {
            in.transferTo(out);
        }

        return out.toString("UTF-8");
    }

    private String realpath(String[] args) {
        String path = args.length > 1 ? args[1] : ".";
        String result = filesystem.realpath(path, currentDirectory);
        if (result.startsWith("realpath:")) return result + "\n";
        return result + "\n";
    }

    private String external(String[] args) throws Exception {
        ProcessBuilder builder = new ProcessBuilder(args);
        builder.directory(currentDirectory);
        builder.redirectErrorStream(true);

        java.util.Map<String, String> variables =
                builder.environment();

        variables.put("PREFIX", env.PREFIX);
        variables.put("HOME", env.HOME);
        variables.put("TMPDIR", env.TMPDIR);
        variables.put("PATH", env.PATH);

        Process process = builder.start();
        byte[] output = process.getInputStream().readAllBytes();
        process.waitFor();

        return new String(output, "UTF-8");
    }

    public String getWorkingDirectory() {
        return currentDirectory.getAbsolutePath();
    }

    public String getStartupMessage() {
        String message = startupError + startupMessage;
        startupError = "";
        startupMessage = "";
        return message;
    }

    // Call this when the terminal session is closed.
    public void close() {
        try {
            configManager.endSession();
        } catch (java.io.IOException e) {
            startupError = "MyLinux filesystem cleanup: " +
                    e.getMessage() + "\n";
        }
    }
}
