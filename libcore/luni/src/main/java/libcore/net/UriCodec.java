package libcore.net;

import java.io.ByteArrayOutputStream;
import java.nio.charset.StandardCharsets;

/** UTF-8 percent-encoding helpers for URI components. */
public final class UriCodec {
    private static final char[] HEX = "0123456789ABCDEF".toCharArray();

    private UriCodec() {
        throw new AssertionError("No instances");
    }

    public static String encode(String value) {
        if (value == null) {
            throw new NullPointerException("value");
        }

        byte[] bytes = value.getBytes(StandardCharsets.UTF_8);
        StringBuilder result = new StringBuilder(bytes.length);

        for (byte item : bytes) {
            int c = item & 0xff;
            if ((c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z') ||
                    (c >= '0' && c <= '9') ||
                    c == '-' || c == '_' || c == '.' || c == '~') {
                result.append((char) c);
            } else {
                result.append('%');
                result.append(HEX[c >>> 4]);
                result.append(HEX[c & 0x0f]);
            }
        }

        return result.toString();
    }

    public static String decode(String value) {
        if (value == null) {
            throw new NullPointerException("value");
        }

        ByteArrayOutputStream bytes = new ByteArrayOutputStream(value.length());

        for (int i = 0; i < value.length();) {
            char c = value.charAt(i);

            if (c == '%') {
                if (i + 2 >= value.length()) {
                    throw new IllegalArgumentException(
                            "Incomplete percent escape");
                }

                int high = Character.digit(value.charAt(i + 1), 16);
                int low = Character.digit(value.charAt(i + 2), 16);

                if (high < 0 || low < 0) {
                    throw new IllegalArgumentException(
                            "Invalid percent escape");
                }

                bytes.write((high << 4) | low);
                i += 3;
            } else {
                int codePoint = value.codePointAt(i);
                byte[] encoded = new String(Character.toChars(codePoint))
                        .getBytes(StandardCharsets.UTF_8);
                bytes.write(encoded, 0, encoded.length);
                i += Character.charCount(codePoint);
            }
        }

        return new String(bytes.toByteArray(), StandardCharsets.UTF_8);
    }
}
