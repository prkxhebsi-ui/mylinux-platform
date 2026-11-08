package android.text.util;

public final class Linkify {
    public static final int WEB_URLS = 0x01;
    public static final int EMAIL_ADDRESSES = 0x02;
    public static final int PHONE_NUMBERS = 0x04;
    public static final int MAP_ADDRESSES = 0x08;
    public static final int ALL = 0x0f;

    private Linkify() {}

    public static boolean addLinks(Object text, int mask) {
        throw new RuntimeException("Stub!");
    }
}
