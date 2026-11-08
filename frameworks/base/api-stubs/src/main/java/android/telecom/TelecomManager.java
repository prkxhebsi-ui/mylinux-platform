package android.telecom;

public class TelecomManager {
    public static final String ACTION_CHANGE_DEFAULT_DIALER =
            "android.telecom.action.CHANGE_DEFAULT_DIALER";

    public boolean isInCall() {
        throw new RuntimeException("Stub!");
    }

    public boolean isInManagedCall() {
        throw new RuntimeException("Stub!");
    }

    public String getDefaultDialerPackage() {
        throw new RuntimeException("Stub!");
    }
}
