package com.example.terminal;

public final class TerminalPathNormalizer {

    private TerminalPathNormalizer() {
    }

    public static String normalize(String path) {
        if (path == null || path.isEmpty()) {
            return ".";
        }

        StringBuilder result = new StringBuilder();
        boolean previousSlash = false;

        for (int i = 0; i < path.length(); i++) {
            char c = path.charAt(i);

            if (c == '/') {
                if (!previousSlash) {
                    result.append('/');
                }
                previousSlash = true;
            } else {
                result.append(c);
                previousSlash = false;
            }
        }

        return result.toString();
    }
}
