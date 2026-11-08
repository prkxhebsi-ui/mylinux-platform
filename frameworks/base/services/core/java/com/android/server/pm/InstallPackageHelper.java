package com.android.server.pm;

import java.io.File;
import java.io.IOException;

public final class InstallPackageHelper {
    private final PackageParser parser = new PackageParser();

    public PackageParser.ParsedPackage validateApk(String path)
            throws IOException {
        if (path == null || path.trim().isEmpty()) {
            throw new IOException("APK path is empty");
        }

        return parser.parsePackage(new File(path));
    }
}
