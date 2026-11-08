package android.telephony;

public class TelephonyManager {
    public static final int SIM_STATE_UNKNOWN = 0;
    public static final int SIM_STATE_ABSENT = 1;
    public static final int SIM_STATE_READY = 5;
    public static final int CALL_STATE_IDLE = 0;
    public static final int CALL_STATE_RINGING = 1;
    public static final int CALL_STATE_OFFHOOK = 2;

    public int getSimState() {
        throw new RuntimeException("Stub!");
    }

    public int getCallState() {
        throw new RuntimeException("Stub!");
    }

    public String getNetworkOperatorName() {
        throw new RuntimeException("Stub!");
    }
}
