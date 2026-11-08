public final class DexTestRunner {
    private static int passed;
    private static int failed;

    private static void test(String name, boolean result) {
        if (result) {
            System.out.println("PASS: " + name);
            passed++;
        } else {
            System.out.println("FAIL: " + name);
            failed++;
        }
    }

    public static void main(String[] args) {
        test("arithmetic", DexArithmeticTest.run());
        test("arrays", DexArrayTest.run());
        test("objects and fields", DexObjectTest.run());
        test("loops and branches", DexControlFlowTest.run());

        System.out.println("Passed: " + passed);
        System.out.println("Failed: " + failed);

        if (failed != 0) {
            throw new AssertionError("Java tests failed");
        }

        System.out.println("ALL JAVA TESTS PASSED");
    }
}
