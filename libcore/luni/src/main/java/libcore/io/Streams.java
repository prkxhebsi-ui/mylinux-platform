package libcore.io;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public final class Streams {
    private Streams() {}

    public static byte[] readFully(InputStream input)
            throws IOException {
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        copy(input, output);
        return output.toByteArray();
    }

    public static void copy(InputStream input, OutputStream output)
            throws IOException {
        byte[] buffer = new byte[8192];
        int count;

        while ((count = input.read(buffer)) != -1) {
            if (count > 0) {
                output.write(buffer, 0, count);
            }
        }
    }

    public static long skipByReading(InputStream input, long amount)
            throws IOException {
        if (amount < 0) {
            throw new IllegalArgumentException("Negative skip amount");
        }

        long skipped = 0;
        byte[] buffer = new byte[4096];

        while (skipped < amount) {
            int wanted = (int) Math.min(buffer.length, amount - skipped);
            int count = input.read(buffer, 0, wanted);

            if (count == -1) break;
            if (count == 0) continue;

            skipped += count;
        }

        return skipped;
    }
}
