package com.android.server.pm;

import com.android.server.SystemService;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public final class PackageManagerService extends SystemService {
    private final Map<String, PackageSetting> packages =
            new LinkedHashMap<>();

    private final InstallPackageHelper installHelper =
            new InstallPackageHelper();

    public PackageManagerService(Object context) {
        super(context);
    }

    @Override
    public void onStart() {
        System.out.println("PackageManagerService started");
    }

    public synchronized void registerPackage(
            String packageName, String apkPath) {

        PackageSetting setting =
                new PackageSetting(packageName, apkPath);

        packages.put(packageName, setting);
    }

    public synchronized PackageSetting getPackage(String packageName) {
        return packages.get(packageName);
    }

    public synchronized boolean removePackage(String packageName) {
        return packages.remove(packageName) != null;
    }

    public synchronized List<PackageSetting> getPackages() {
        return Collections.unmodifiableList(
                new ArrayList<>(packages.values()));
    }

    public InstallPackageHelper getInstallHelper() {
        return installHelper;
    }
}
