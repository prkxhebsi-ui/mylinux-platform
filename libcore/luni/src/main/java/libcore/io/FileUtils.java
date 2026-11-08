package libcore.io;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public final class FileUtils {
    private FileUtils() {}

    public static byte[] readFile(Path path) throws IOException {
        return Files.readAllBytes(path);
    }

    public static String readText(Path path) throws IOException {
        return Files.readString(path);
    }

    public static void writeFile(Path path, byte[] data)
            throws IOException {
        Path parent = path.toAbsolutePath().getParent();

        if (parent != null) {
            Files.createDirectories(parent);
        }

        Files.write(path, data);
    }

    public static void writeText(Path path, String text)
            throws IOException {
        Path parent = path.toAbsolutePath().getParent();

        if (parent != null) {
            Files.createDirectories(parent);
        }

        Files.writeString(path, text);
    }

    public static void move(Path source, Path destination)
            throws IOException {
        Files.move(source, destination,
                StandardCopyOption.REPLACE_EXISTING);
    }

    public static boolean exists(Path path) {
        return Files.exists(path);
    }
}
