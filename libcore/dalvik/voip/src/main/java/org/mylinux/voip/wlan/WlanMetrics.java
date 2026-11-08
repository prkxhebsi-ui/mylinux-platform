package org.mylinux.voip.wlan;

public final class WlanMetrics {
    private final String interfaceName;
    private final Integer rssiDbm;
    private final Integer linkQuality;
    private final Integer noiseDbm;
    private final String operatingState;
    private final boolean carrier;
    private final String macAddress;

    public WlanMetrics(
            String interfaceName,
            Integer rssiDbm,
            Integer linkQuality,
            Integer noiseDbm,
            String operatingState,
            boolean carrier,
            String macAddress) {

        this.interfaceName = interfaceName;
        this.rssiDbm = rssiDbm;
        this.linkQuality = linkQuality;
        this.noiseDbm = noiseDbm;
        this.operatingState = operatingState;
        this.carrier = carrier;
        this.macAddress = macAddress;
    }

    public String getInterfaceName() {
        return interfaceName;
    }

    public Integer getRssiDbm() {
        return rssiDbm;
    }

    public Integer getLinkQuality() {
        return linkQuality;
    }

    public Integer getNoiseDbm() {
        return noiseDbm;
    }

    public String getOperatingState() {
        return operatingState;
    }

    public boolean hasCarrier() {
        return carrier;
    }

    public String getMacAddress() {
        return macAddress;
    }

    public boolean hasRssi() {
        return rssiDbm != null;
    }
}
