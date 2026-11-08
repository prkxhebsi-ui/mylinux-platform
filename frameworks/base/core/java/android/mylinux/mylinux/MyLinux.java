package android.mylinux.mylinux;

import java.io.File;
import java.io.IOException;

public final class MyLinux {
    private final MyLinuxConfig config = new MyLinuxConfig();
    private final MyLinuxEnvironment environment =
        new MyLinuxEnvironment();

    public void initialize(File confFile, File envsFile)
            throws IOException {
        config.load(confFile);
        environment.load(envsFile);
    }

    public MyLinuxConfig getConfig() {
        return config;
    }

    public MyLinuxEnvironment getEnvironment() {
        return environment;
    }
}
