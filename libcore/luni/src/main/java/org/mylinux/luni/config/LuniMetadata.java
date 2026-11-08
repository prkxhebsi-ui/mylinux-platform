package org.mylinux.luni.config;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

import org.json.JSONObject;

public final class LuniMetadata {

    private final JSONObject json;

    private LuniMetadata(JSONObject json) {
        this.json = json;
    }

    public static LuniMetadata load(File file)
            throws IOException {

        ByteArrayOutputStream output =
                new ByteArrayOutputStream();

        try (InputStream input = new FileInputStream(file)) {
            byte[] buffer = new byte[4096];
            int count;

            while ((count = input.read(buffer)) != -1) {
                output.write(buffer, 0, count);
            }
        }

        String content = new String(
                output.toByteArray(),
                StandardCharsets.UTF_8);

        try {
            return new LuniMetadata(new JSONObject(content));
        } catch (RuntimeException exception) {
            throw new IOException(
                    "Invalid Luni JSON metadata", exception);
        }
    }

    public String getName() {
        return json.optString("name", "MyLinux Luni");
    }

    public String getId() {
        return json.optString("id", "org.mylinux.luni");
    }

    public int getApiLevel() {
        return json.optInt("apiLevel", 0);
    }

    public String getArchitecture() {
        return json.optString("architecture", "unknown");
    }

    public JSONObject getComponents() {
        return json.optJSONObject("components");
    }

    public JSONObject getRawMetadata() {
        return json;
    }
}
