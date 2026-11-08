package org.mylinux.voip.network;

public final class VoipSignal {
    public enum Level {
        UNKNOWN,
        EXCELLENT,
        GOOD,
        FAIR,
        POOR
    }

    private VoipSignal() {
    }

    public static Level fromRssi(Integer rssiDbm) {
        if (rssiDbm == null) {
            return Level.UNKNOWN;
        }

        if (rssiDbm >= -55) {
            return Level.EXCELLENT;
        }

        if (rssiDbm >= -67) {
            return Level.GOOD;
        }

        if (rssiDbm >= -75) {
            return Level.FAIR;
        }

        return Level.POOR;
    }

    public static String describe(Integer rssiDbm) {
        Level level = fromRssi(rssiDbm);

        switch (level) {
            case EXCELLENT:
                return "Excellent signal";

            case GOOD:
                return "Good signal";

            case FAIR:
                return "Fair signal";

            case POOR:
                return "Weak signal";

            default:
                return "Signal unavailable";
        }
    }
}
