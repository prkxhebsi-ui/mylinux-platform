package com.mylinux.packageinstaller;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.pm.PackageInstaller;
import android.os.Bundle;

import java.io.File;
import java.io.FileInputStream;
import java.io.OutputStream;
import java.io.IOException;

public final class InstallActivity extends Activity {

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);

        String path = getIntent().getStringExtra("apk_path");

        if (path == null) {
            showError("No APK path was supplied.");
            return;
        }

        installApk(path);
    }

    private void installApk(String path) {
        File apk = new File(path);

        if (!apk.isFile() || !apk.canRead()
                || !apk.getName().toLowerCase().endsWith(".apk")) {
            showError("APK file is missing or cannot be read.");
            return;
        }

        PackageInstaller installer =
                getPackageManager().getPackageInstaller();

        PackageInstaller.SessionParams params =
                new PackageInstaller.SessionParams(
                        PackageInstaller.SessionParams.MODE_FULL_INSTALL);

        int sessionId;

        try {
            sessionId = installer.createSession(params);

            try (PackageInstaller.Session session =
                         installer.openSession(sessionId)) {

                try (FileInputStream input = new FileInputStream(apk);
                     OutputStream output =
                             session.openWrite("base.apk", 0, apk.length())) {

                    byte[] buffer = new byte[65536];
                    int count;

                    while ((count = input.read(buffer)) != -1) {
                        output.write(buffer, 0, count);
                    }

                    session.fsync(output);
                }

                Intent callback = new Intent(
                        this, InstallResultReceiver.class);

                callback.setAction(
                        InstallResultReceiver.ACTION_INSTALL_RESULT);

                PendingIntent pending = PendingIntent.getBroadcast(
                        this,
                        sessionId,
                        callback,
                        PendingIntent.FLAG_UPDATE_CURRENT);

                session.commit(pending.getIntentSender());
            }

        } catch (IOException | RuntimeException error) {
            showError("Installation could not start: "
                    + error.getMessage());
        }
    }

    private void showError(String message) {
        System.err.println("MyLinux Package Installer: " + message);
        finish();
    }
}
