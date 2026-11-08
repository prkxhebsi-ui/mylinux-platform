package com.android.server.pm;

import com.android.server.SystemService;
import java.io.File;

public final class PackageInstallerService extends SystemService {
    public static final String INSTALLER_PACKAGE =
            "com.mylinux.packageinstaller";

    public PackageInstallerService(Object context) {
        super(context);
    }

    @Override
    public void onStart() {
        System.out.println("PackageInstallerService started");
    }

    public String getInstallerPackageName() {
        return INSTALLER_PACKAGE;
    }

    public boolean isValidApkPath(String path) {
        if (path == null) return false;

        File apk = new File(path);

        return apk.isFile()
                && apk.canRead()
                && apk.getName().toLowerCase().endsWith(".apk");
    }
}
