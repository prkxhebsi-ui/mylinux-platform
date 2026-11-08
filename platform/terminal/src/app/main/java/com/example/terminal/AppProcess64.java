package com.example.terminal;

import android.content.Context;
import android.os.Build;
import android.os.Process;
import android.util.Log;

import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import java.util.Arrays;

public final class AppProcess64 {

    private static final String TAG = "AppProcess64";
    private final Context context;

    public AppProcess64(Context context) {
        this.context = context.getApplicationContext();
    }

    public boolean isSupported() {
        return Process.is64Bit()
                && Arrays.asList(Build.SUPPORTED_64_BIT_ABIS)
                        .contains("arm64-v8a");
    }

    public int execute(String[] args) {
        if (!isSupported()) {
            Log.e(TAG, "64-bit execution is not supported");
            return 1;
        }

        if (args == null || args.length == 0) {
            Log.i(TAG, "Usage: app_process64 <class> [arguments]");
            return 2;
        }

        if ("--help".equals(args[0])) {
            Log.i(TAG, "Usage: app_process64 <class> [arguments]");
            return 0;
        }

        if ("--version".equals(args[0])) {
            Log.i(TAG, "MyLinux app_process64 1.0");
            return 0;
        }

        String className = args[0];
        String[] classArgs = Arrays.copyOfRange(
                args, 1, args.length);

        try {
            ClassLoader loader = context.getClassLoader();
            Class<?> entry = Class.forName(className, true, loader);

            Method main = entry.getMethod(
                    "main", String[].class);

            if (main.getReturnType() != void.class) {
                Log.e(TAG, "main() must return void");
                return 1;
            }

            main.invoke(null, (Object) classArgs);
            return 0;

        } catch (InvocationTargetException e) {
            Log.e(TAG, "Application entry point failed",
                    e.getCause());
            return 1;
        } catch (ReflectiveOperationException |
                 LinkageError e) {
            Log.e(TAG, "Cannot launch: " + className, e);
            return 1;
        }
    }
}
