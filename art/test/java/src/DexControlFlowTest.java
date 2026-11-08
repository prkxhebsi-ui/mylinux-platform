public final class DexControlFlowTest {
    static int sum(int limit) {
        int result = 0;

        for (int i = 1; i <= limit; i++) {
            if ((i % 2) == 0) {
                result += i;
            }
        }

        return result;
    }

    public static boolean run() {
        return sum(10) == 30;
    }
}
