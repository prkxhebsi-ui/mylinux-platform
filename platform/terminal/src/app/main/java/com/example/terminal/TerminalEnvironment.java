package com.example.terminal;

public final class TerminalEnvironment {
    public final String PREFIX;
    public final String HOME;
    public final String TMPDIR;
    public final String PATH;

    public TerminalEnvironment(TerminalPaths paths) {
        if (paths == null) {
            throw new IllegalArgumentException("Paths cannot be null");
        }

        PREFIX = paths.prefix;
        HOME = paths.home;
        TMPDIR = PREFIX + "/tmp";
        PATH = PREFIX + "/bin";
    }

    public String get(String name) {
        if ("PREFIX".equals(name)) return PREFIX;
        if ("HOME".equals(name)) return HOME;
        if ("TMPDIR".equals(name)) return TMPDIR;
        if ("PATH".equals(name)) return PATH;
        return null;
    }

    public String[] names() {
        return new String[] {
            "PREFIX",
            "HOME",
            "TMPDIR",
            "PATH"
        };
    }

    public String[] values() {
        return new String[] {
            PREFIX,
            HOME,
            TMPDIR,
            PATH
        };
    }
}
