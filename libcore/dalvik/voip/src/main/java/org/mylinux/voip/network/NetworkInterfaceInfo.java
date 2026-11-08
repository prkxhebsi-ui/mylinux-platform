package org.mylinux.voip.network;

import java.io.File;

public final class NetworkInterfaceInfo {
    private NetworkInterfaceInfo() {
    }

    public static boolean exists(String interfaceName) {
        if (interfaceName == null ||
                !interfaceName.matches("[A-Za-z0-9_.-]+")) {
            return false;
        }

        return new File(
                "/sys/class/net", interfaceName).isDirectory();
    }

    public static boolean isWlanPresent() {
        return exists("wlan0");
    }

    public static boolean isWlanUp() {
        if (!isWlanPresent()) {
            return false;
        }

        try {
            File state = new File(
                    "/sys/class/net/wlan0/operstate");

            if (!state.isFile() || !state.canRead()) {
                return false;
            }

            byte[] data = new byte[32];

            try (java.io.FileInputStream input =
                    new java.io.FileInputStream(state)) {

                int count = input.read(data);

                if (count <= 0) {
                    return false;
                }

                String value = new String(
                        data, 0, count, "UTF-8").trim();

                return "up".equals(value);
            }
        } catch (Exception exception) {
            return false;
        }
    }
}
