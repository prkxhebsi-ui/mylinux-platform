public final class DexArrayTest {
    public static boolean run() {
        int[] values = new int[5];

        for (int i = 0; i < values.length; i++) {
            values[i] = (i + 1) * 10;
        }

        return values[0] == 10
            && values[2] == 30
            && values[4] == 50
            && values.length == 5;
    }
}
