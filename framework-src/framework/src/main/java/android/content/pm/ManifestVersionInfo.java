package android.content.pm;

public final class ManifestVersionInfo {
    public int minSdkVersion;
    public int targetSdkVersion;
    public int maximumSdkVersion;
    public int platformSdkVersion;
    public String codename;
    public ManifestGeneration generation = ManifestGeneration.PRESENT;

    public boolean supportsPlatform() {
        if (platformSdkVersion < minSdkVersion) return false;

        if (maximumSdkVersion > 0
                && platformSdkVersion > maximumSdkVersion) {
            return false;
        }

        return true;
    }

    public boolean targetIsNewerThanPlatform() {
        return targetSdkVersion > platformSdkVersion;
    }

    public boolean isOlderThan(int sdk) {
        return targetSdkVersion < sdk;
    }

    public boolean isNewerThan(int sdk) {
        return targetSdkVersion > sdk;
    }
}
