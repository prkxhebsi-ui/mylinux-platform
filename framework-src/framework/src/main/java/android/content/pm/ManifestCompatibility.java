package android.content.pm;

public final class ManifestCompatibility {
    public ManifestVersionInfo readVersion(ManifestDocument document) {
        ManifestVersionInfo info = new ManifestVersionInfo();

        if (document == null || document.root == null) return info;

        ManifestNode sdk = document.root.getChild("uses-sdk");

        if (sdk != null) {
            info.minSdkVersion = parseSdk(
                    sdk.getAttribute("android:minSdkVersion"), 1);

            info.targetSdkVersion = parseSdk(
                    sdk.getAttribute("android:targetSdkVersion"),
                    info.minSdkVersion);

            info.maximumSdkVersion = parseSdk(
                    sdk.getAttribute("android:maxSdkVersion"), 0);
        }

        return info;
    }

    public boolean isCompatible(
            ManifestDocument document, int platformSdk) {
        ManifestVersionInfo info = readVersion(document);
        info.platformSdkVersion = platformSdk;
        return info.supportsPlatform();
    }

    public ManifestGeneration classify(
            ManifestDocument document, int platformSdk) {
        ManifestVersionInfo info = readVersion(document);

        if (info.minSdkVersion > platformSdk) {
            return ManifestGeneration.NEWEST;
        }

        if (info.targetSdkVersion > platformSdk) {
            return ManifestGeneration.NEWER;
        }

        if (info.targetSdkVersion == platformSdk) {
            return ManifestGeneration.PRESENT;
        }

        if (info.targetSdkVersion >= platformSdk - 2) {
            return ManifestGeneration.NEW;
        }

        if (info.targetSdkVersion >= platformSdk - 5) {
            return ManifestGeneration.OLD;
        }

        if (info.targetSdkVersion >= 1) {
            return ManifestGeneration.OLDER;
        }

        return ManifestGeneration.OLDEST;
    }

    private int parseSdk(String value, int fallback) {
        if (value == null || value.length() == 0) return fallback;

        try {
            return Integer.parseInt(value);
        } catch (NumberFormatException error) {
            return fallback;
        }
    }
}
