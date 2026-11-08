package android.speech.tts;

public class TextToSpeech {
    public static final int SUCCESS = 0;
    public static final int ERROR = -1;
    public static final int QUEUE_FLUSH = 0;
    public static final int QUEUE_ADD = 1;

    public int speak(String text, int queueMode, Object parameters, String id) {
        throw new RuntimeException("Stub!");
    }

    public int stop() {
        throw new RuntimeException("Stub!");
    }

    public void shutdown() {
        throw new RuntimeException("Stub!");
    }
}
