package com.example.terminal;

public final class TerminalColors {
    private static final String RESET = "\033[0m";
    private static final String GREEN = "\033[32m";
    private static final String PURPLE = "\033[35m";
    private static final String PINK = "\033[95m";
    private static final String BLUE = "\033[34m";
    private static final String WHITE = "\033[37m";
    private static final String GREEN_BG = "\033[42;30m";
    private static final String RED_BG = "\033[41;37m";

    private TerminalColors() {}

    public static String color(java.io.File file) {
        String name = file.getName();

        if (name.equals("su") ||
            name.equals("mount") ||
            name.equals("umount")) {
            return RED_BG;
        }

        try {
            android.system.StructStat stat =
                android.system.Os.lstat(file.getAbsolutePath());

            int mode = stat.st_mode;
            int type = mode & 0170000;

            if ((mode & 01000) != 0 &&
                (mode & 00111) != 0) {
                return GREEN_BG;
            }

            if (type == 0120000) return BLUE;
            if (type == 0140000) return PINK;
            if (type == 0040000) return PURPLE;
            if ((mode & 00111) != 0) return GREEN;

        } catch (Exception ignored) {
            if (file.isDirectory()) return PURPLE;
            if (file.canExecute()) return GREEN;
        }

        return WHITE;
    }

    public static String paint(java.io.File file) {
        return color(file) + file.getName() + RESET;
    }
}
