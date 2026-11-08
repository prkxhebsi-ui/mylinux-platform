package android.content.pm;

import java.util.List;

public abstract class PackageManager {
    public static final int GET_ACTIVITIES = 0x00000001;
    public static final int GET_RECEIVERS = 0x00000002;
    public static final int GET_SERVICES = 0x00000004;
    public static final int GET_PROVIDERS = 0x00000008;
    public static final int GET_INSTRUMENTATION = 0x00000010;
    public static final int GET_PERMISSIONS = 0x00001000;
    public static final int GET_META_DATA = 0x00000080;
    public static final int GET_SHARED_LIBRARY_FILES = 0x00000400;
    public static final int MATCH_DISABLED_COMPONENTS = 0x00000200;

    public static final int PERMISSION_GRANTED = 0;
    public static final int PERMISSION_DENIED = -1;

    public abstract PackageInfo getPackageInfo(
            String packageName, int flags);

    public abstract ApplicationInfo getApplicationInfo(
            String packageName, int flags);

    public abstract boolean hasSystemFeature(String feature);

    public List<PackageInfo> getInstalledPackages(int flags) {
        throw new UnsupportedOperationException("API stub");
    }

    public List<ApplicationInfo> getInstalledApplications(int flags) {
        throw new UnsupportedOperationException("API stub");
    }

    public CharSequence getApplicationLabel(ApplicationInfo info) {
        throw new UnsupportedOperationException("API stub");
    }

    public int checkPermission(String permission, String packageName) {
        throw new UnsupportedOperationException("API stub");
    }

    public abstract static class NameNotFoundException
            extends Exception {
        public NameNotFoundException() {
            super();
        }

        public NameNotFoundException(String message) {
            super(message);
        }
    }
}
