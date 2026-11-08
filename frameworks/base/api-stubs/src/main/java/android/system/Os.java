package android.system;

public final class Os {
    private Os() {}

    public static void chmod(String path, int mode)
            throws ErrnoException {
        throw new UnsupportedOperationException(
                "Os.chmod is an API stub");
    }

    public static StructStat lstat(String path)
            throws ErrnoException {
        throw new UnsupportedOperationException(
                "Os.lstat is an API stub");
    }
}
