package libcore.util;

public final class HexDump {
    private static final char[] HEX =
            "0123456789abcdef".toCharArray();

    private HexDump() {}

    public static String toHexString(byte[] data) {
        if (data == null) return "null";

        char[] result = new char[data.length * 2];

        for (int i = 0; i < data.length; i++) {
            int value = data[i] & 0xff;
            result[i * 2] = HEX[value >>> 4];
            result[i * 2 + 1] = HEX[value & 0x0f];
        }

        return new String(result);
    }

    public static String dump(byte[] data) {
        if (data == null) return "null";

        StringBuilder output = new StringBuilder();

        for (int i = 0; i < data.length; i += 16) {
            output.append(String.format("%08x  ", i));

            int end = Math.min(i + 16, data.length);

            for (int j = i; j < end; j++) {
                output.append(String.format("%02x ", data[j] & 0xff));
            }

            output.append('\n');
        }

        return output.toString();
    }
}
