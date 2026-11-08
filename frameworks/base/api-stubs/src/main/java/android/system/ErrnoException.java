package android.system;

public class ErrnoException extends Exception {
    private static final long serialVersionUID = 1L;

    public final String functionName;
    public final int errno;

    public ErrnoException(String functionName, int errno) {
        super(functionName + " failed: errno " + errno);
        this.functionName = functionName;
        this.errno = errno;
    }

    public ErrnoException(
            String functionName, int errno, Throwable cause) {
        super(functionName + " failed: errno " + errno, cause);
        this.functionName = functionName;
        this.errno = errno;
    }
}
