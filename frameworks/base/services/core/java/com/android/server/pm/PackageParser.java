package com.android.server.pm;

import java.io.File;
import java.io.IOException;
import java.util.zip.ZipFile;

public final class PackageParser {

    public static final class ParsedPackage {
        public final File apkFile;
        public final long fileSize;

        ParsedPackage(File apkFile) {
            this.apkFile = apkFile;
            this.fileSize = apkFile.length();
        }
    }

    public ParsedPackage parsePackage(File apkFile) throws IOException {
        if (apkFile == null || !apkFile.isFile()) {
            throw new IOException("APK file does not exist");
        }

        if (!apkFile.getName().toLowerCase().endsWith(".apk")) {
            throw new IOException("File is not an APK");
        }

        try (ZipFile zip = new ZipFile(apkFile)) {
            if (zip.getEntry("AndroidManifest.xml") == null) {
                throw new IOException("APK has no AndroidManifest.xml");
            }
        }

        return new ParsedPackage(apkFile);
    }
}
