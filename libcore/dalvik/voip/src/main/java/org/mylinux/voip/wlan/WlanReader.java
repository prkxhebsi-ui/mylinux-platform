package org.mylinux.voip.wlan;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public final class WlanReader {
    private static final String DEFAULT_PROC =
            "/proc/net/wireless";

    private static final String DEFAULT_SYS =
            "/sys/class/net";

    private WlanReader() {
    }

    private static String readText(File file) {
        if (!file.isFile() || !file.canRead()) {
            return null;
        }

        try (BufferedReader reader = new BufferedReader(
                new FileReader(file))) {
            return reader.readLine();
        } catch (IOException exception) {
            return null;
        }
    }

    private static Integer parseNumber(String value) {
        if (value == null) {
            return null;
        }

        try {
            String cleaned = value.replaceAll("[^0-9+.-]", "");
            if (cleaned.length() == 0) {
                return null;
            }

            return (int) Math.round(
                    Double.parseDouble(cleaned));
        } catch (NumberFormatException exception) {
            return null;
        }
    }

    private static String[] readWirelessRow(
            String interfaceName,
            File wirelessFile) {

        if (!wirelessFile.isFile() || !wirelessFile.canRead()) {
            return null;
        }

        try (BufferedReader reader =
                new BufferedReader(new FileReader(wirelessFile))) {

            String line;

            while ((line = reader.readLine()) != null) {
                int colon = line.indexOf(':');

                if (colon < 0) {
                    continue;
                }

                String name = line.substring(0, colon).trim();

                if (!interfaceName.equals(name)) {
                    continue;
                }

                return line.substring(colon + 1)
                        .trim()
                        .split("\\s+");
            }
        } catch (IOException exception) {
            return null;
        }

        return null;
    }

    public static WlanMetrics read(String interfaceName) {
        return read(interfaceName,
                DEFAULT_PROC, DEFAULT_SYS);
    }

    public static WlanMetrics read(
            String interfaceName,
            String procDirectory,
            String sysDirectory) {

        if (interfaceName == null ||
                !interfaceName.matches("[A-Za-z0-9_.-]+")) {
            throw new IllegalArgumentException(
                    "Invalid network interface name");
        }

        File procWireless =
                new File(procDirectory, "wireless");

        File interfaceDirectory =
                new File(sysDirectory, interfaceName);

        String[] row = readWirelessRow(
                interfaceName, procWireless);

        Integer linkQuality = null;
        Integer rssi = null;
        Integer noise = null;

        if (row != null && row.length >= 4) {
            linkQuality = parseNumber(row[1]);
            rssi = parseNumber(row[2]);
            noise = parseNumber(row[3]);
        }

        String state = readText(
                new File(interfaceDirectory, "operstate"));

        String carrierText = readText(
                new File(interfaceDirectory, "carrier"));

        String mac = readText(
                new File(interfaceDirectory, "address"));

        boolean carrier = "1".equals(
                carrierText == null ? "" : carrierText.trim());

        return new WlanMetrics(
                interfaceName,
                rssi,
                linkQuality,
                noise,
                state,
                carrier,
                mac);
    }
}
