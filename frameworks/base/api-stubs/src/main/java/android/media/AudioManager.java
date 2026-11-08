package android.media;

public class AudioManager {
    public static final int STREAM_VOICE_CALL = 0;
    public static final int STREAM_SYSTEM = 1;
    public static final int STREAM_RING = 2;
    public static final int STREAM_MUSIC = 3;
    public static final int MODE_NORMAL = 0;
    public static final int MODE_IN_CALL = 2;
    public static final int MODE_IN_COMMUNICATION = 3;

    public void setMode(int mode) {
        throw new RuntimeException("Stub!");
    }

    public int getMode() {
        throw new RuntimeException("Stub!");
    }

    public void setSpeakerphoneOn(boolean enabled) {
        throw new RuntimeException("Stub!");
    }

    public boolean isSpeakerphoneOn() {
        throw new RuntimeException("Stub!");
    }
}
