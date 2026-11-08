package android.os;

public final class Build {
    private Build() {}

    public static final String MODEL = "unknown";
    public static final String MANUFACTURER = "unknown";
    public static final String BRAND = "unknown";
    public static final String DEVICE = "unknown";
    public static final String PRODUCT = "unknown";
    public static final String HARDWARE = "unknown";
    public static final String TYPE = "userdebug";
    public static final String TAGS = "dev-keys";
    public static final String FINGERPRINT = "unknown";
    public static final String ID = "unknown";
    public static final String HOST = "unknown";
    public static final String USER = "unknown";
    public static final String CPU_ABI = "unknown";
    public static final String CPU_ABI2 = "unknown";
    public static final boolean IS_DEBUGGABLE = false;

    public static final String[] SUPPORTED_ABIS = {};
    public static final String[] SUPPORTED_32_BIT_ABIS = {};
    public static final String[] SUPPORTED_64_BIT_ABIS = {};

    public static final class VERSION {
        private VERSION() {}

        public static final String RELEASE = "unknown";
        public static final String INCREMENTAL = "unknown";
        public static final String CODENAME = "REL";
        public static final String SECURITY_PATCH = "unknown";
        public static final String BASE_OS = "unknown";
        public static final int SDK_INT = 30;
        public static final int PREVIEW_SDK_INT = 0;
    }

    public static final class VERSION_CODES {
        private VERSION_CODES() {}

        public static final int BASE = 1;
        public static final int LOLLIPOP = 21;
        public static final int MARSHMALLOW = 23;
        public static final int O = 26;
        public static final int P = 28;
        public static final int Q = 29;
        public static final int R = 30;
    }
}
