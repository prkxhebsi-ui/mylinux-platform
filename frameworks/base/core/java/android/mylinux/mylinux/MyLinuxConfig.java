package android.mylinux.mylinux;

import android.mylinux.confparser.ConfRegistry;
import java.io.File;
import java.io.IOException;

public final class MyLinuxConfig {
    private final ConfRegistry registry = new ConfRegistry();

    public void load(File file) throws IOException {
        registry.load(file);
    }

    public String get(String section, String key) {
        return registry.get(section, key);
    }

    public String getSystemName() {
        return get("system", "name");
    }

    public String getArchitecture() {
        return get("system", "architecture");
    }

    public String getApiLevel() {
        return get("system", "api");
    }

    public ConfRegistry getRegistry() {
        return registry;
    }
}
