public final class DexArithmeticTest {
    public static boolean run() {
        int a = 12;
        int b = 5;

        return a + b == 17
            && a - b == 7
            && a * b == 60
            && a / b == 2
            && a % b == 2;
    }
}
