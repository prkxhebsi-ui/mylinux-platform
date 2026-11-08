package com.mylinux.packageinstaller;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInstaller;

public final class InstallResultReceiver extends BroadcastReceiver {

    public static final String ACTION_INSTALL_RESULT =
            "com.mylinux.packageinstaller.INSTALL_RESULT";

    @Override
    public void onReceive(Context context, Intent intent) {
        int status = intent.getIntExtra(
                PackageInstaller.EXTRA_STATUS,
                PackageInstaller.STATUS_FAILURE);

        String message = intent.getStringExtra(
                PackageInstaller.EXTRA_STATUS_MESSAGE);

        if (status == PackageInstaller.STATUS_SUCCESS) {
            System.out.println("MyLinux: APK installed successfully.");
            return;
        }

        if (status == PackageInstaller.STATUS_PENDING_USER_ACTION) {
            Intent confirmation =
                    intent.getParcelableExtra(Intent.EXTRA_INTENT);

            if (confirmation != null) {
                confirmation.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(confirmation);
            }
            return;
        }

        System.err.println("MyLinux: APK installation failed: " + message);
    }
}
