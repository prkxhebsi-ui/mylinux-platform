package android.mylinux.mylinux;

import android.mylinux.envsparser.EnvsEntry;
import android.mylinux.envsparser.EnvsRegistry;
import java.io.File;
import java.io.IOException;

public final class MyLinuxEnvironment {
    private final EnvsRegistry registry = new EnvsRegistry();

    public void load(File file) throws IOException {
        registry.load(file);
    }

    public EnvsEntry getSymbol(String symbol) {
        return registry.getSymbol(symbol);
    }

    public EnvsEntry getType(String type) {
        return registry.getType(type);
    }

    public EnvsRegistry getRegistry() {
        return registry;
    }
}
