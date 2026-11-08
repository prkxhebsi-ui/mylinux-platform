package libcore.util;

/** Converts byte arrays to and from hexadecimal representations. */
public final class HexEncoding {
    private static final char[] HEX_DIGITS =
            "0123456789abcdef".toCharArray();

    private HexEncoding() {
        throw new AssertionError("No instances");
    }

    public static String encodeToString(byte[] data) {
        if (data == null) {
            throw new NullPointerException("data");
        }

        char[] result = new char[data.length * 2];
        for (int i = 0; i < data.length; i++) {
            int value = data[i] & 0xff;
            result[i * 2] = HEX_DIGITS[value >>> 4];
            result[i * 2 + 1] = HEX_DIGITS[value & 0x0f];
        }
        return new String(result);
    }

    public static byte[] decode(String encoded) {
        if (encoded == null) {
            throw new NullPointerException("encoded");
        }
        if ((encoded.length() & 1) != 0) {
            throw new IllegalArgumentException(
                    "Hexadecimal input must have even length");
        }

        byte[] result = new byte[encoded.length() / 2];
        for (int i = 0; i < result.length; i++) {
            int high = Character.digit(encoded.charAt(i * 2), 16);
            int low = Character.digit(encoded.charAt(i * 2 + 1), 16);

            if (high < 0 || low < 0) {
                throw new IllegalArgumentException(
                        "Invalid hexadecimal character");
            }

            result[i] = (byte) ((high << 4) | low);
        }
        return result;
    }
}
