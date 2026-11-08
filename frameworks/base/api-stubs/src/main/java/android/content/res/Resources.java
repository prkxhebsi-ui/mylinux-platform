package android.content.res;

public class Resources {
    public static class NotFoundException extends RuntimeException {
        public NotFoundException(String message) {
            super(message);
        }
    }

    public String getString(int id) {
        throw new RuntimeException("Stub!");
    }

    public int getInteger(int id) {
        throw new RuntimeException("Stub!");
    }

    public boolean getBoolean(int id) {
        throw new RuntimeException("Stub!");
    }

    public Object getDrawable(int id) {
        throw new RuntimeException("Stub!");
    }
}
