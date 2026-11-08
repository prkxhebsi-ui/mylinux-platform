package android.hardware;

public class SensorManager {
    public static final int SENSOR_DELAY_NORMAL = 3;
    public static final int SENSOR_DELAY_UI = 2;
    public static final int SENSOR_DELAY_GAME = 1;
    public static final int SENSOR_DELAY_FASTEST = 0;

    public Object getDefaultSensor(int type) {
        throw new RuntimeException("Stub!");
    }

    public boolean registerListener(Object listener, Object sensor, int rate) {
        throw new RuntimeException("Stub!");
    }

    public void unregisterListener(Object listener) {
        throw new RuntimeException("Stub!");
    }
}
