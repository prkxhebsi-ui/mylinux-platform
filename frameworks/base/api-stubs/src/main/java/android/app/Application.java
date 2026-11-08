package android.app;

import android.content.Context;
import android.os.Bundle;

public class Application extends Context {
    public Application() {}

    protected void attachBaseContext(Context base) {}

    public void onCreate() {}

    public void onTerminate() {}

    public void onConfigurationChanged(Object configuration) {}

    public void onLowMemory() {}

    public void onTrimMemory(int level) {}

    public void registerActivityLifecycleCallbacks(
            Object callbacks) {}

    public void unregisterActivityLifecycleCallbacks(
            Object callbacks) {}

    public void registerComponentCallbacks(Object callbacks) {}

    public void unregisterComponentCallbacks(Object callbacks) {}

    @Override
    public Object getSystemService(String name) {
        throw new UnsupportedOperationException("API stub");
    }

    @Override
    public String getPackageName() {
        throw new UnsupportedOperationException("API stub");
    }

    @Override
    public java.io.File getFilesDir() {
        throw new UnsupportedOperationException("API stub");
    }

    @Override
    public java.io.File getCacheDir() {
        throw new UnsupportedOperationException("API stub");
    }
}
