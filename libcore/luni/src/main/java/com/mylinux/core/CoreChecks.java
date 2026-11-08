package com.mylinux.core;

import java.util.Objects;

/** Small validation helpers shared by MyLinux Java components. */
public final class CoreChecks {
    private CoreChecks() {
    }

    public static String requireNonEmpty(String value, String name) {
        Objects.requireNonNull(value, name);
        if (value.isEmpty()) {
            throw new IllegalArgumentException(name + " must not be empty");
        }
        return value;
    }

    public static String requireNonBlank(String value, String name) {
        Objects.requireNonNull(value, name);
        if (value.trim().isEmpty()) {
            throw new IllegalArgumentException(name + " must not be blank");
        }
        return value;
    }

    public static int requireNonNegative(int value, String name) {
        if (value < 0) {
            throw new IllegalArgumentException(name + " must be non-negative");
        }
        return value;
    }

    public static long requireNonNegative(long value, String name) {
        if (value < 0) {
            throw new IllegalArgumentException(name + " must be non-negative");
        }
        return value;
    }

    public static int requireInRange(
            int value, int minimum, int maximum, String name) {
        if (minimum > maximum || value < minimum || value > maximum) {
            throw new IllegalArgumentException(name + " is outside the allowed range");
        }
        return value;
    }
}
