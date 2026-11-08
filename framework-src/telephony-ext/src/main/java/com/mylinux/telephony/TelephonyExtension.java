package com.mylinux.telephony;

/**
 * MyLinux telephony extension prototype.
 *
 * This class does not access SIM cards or modem hardware.
 */
public final class TelephonyExtension {

    public static final int NETWORK_UNKNOWN = 0;
    public static final int NETWORK_WIFI = 1;
    public static final int NETWORK_CELLULAR = 2;

    private TelephonyExtension() {
    }

    public static String getExtensionName() {
        return "MyLinux Telephony Extension";
    }
}
