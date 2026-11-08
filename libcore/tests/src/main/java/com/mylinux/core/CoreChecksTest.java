package com.mylinux.core;

public final class CoreChecksTest {
    private CoreChecksTest() {
    }

    public static void main(String[] args) {
        check("valid text".equals(
                CoreChecks.requireNonEmpty("valid text", "value")));

        check(CoreChecks.requireNonNegative(10, "count") == 10);
        check(CoreChecks.requireInRange(3, 1, 5, "level") == 3);

        expectIllegalArgument(
                () -> CoreChecks.requireNonEmpty("", "value"));

        expectIllegalArgument(
                () -> CoreChecks.requireNonNegative(-1, "count"));

        check(RuntimeInfo.availableProcessors() >= 1);
        check(RuntimeDiagnostics.snapshot().containsKey("java.version"));

        System.out.println("MyLinux CoreChecksTest: PASS");
    }

    private static void check(boolean condition) {
        if (!condition) {
            throw new AssertionError("Test failed");
        }
    }

    private static void expectIllegalArgument(Runnable action) {
        try {
            action.run();
        } catch (IllegalArgumentException expected) {
            return;
        }

        throw new AssertionError("Expected IllegalArgumentException");
    }
}
