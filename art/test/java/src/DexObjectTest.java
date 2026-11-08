public final class DexObjectTest {
    static final class Counter {
        int value;

        Counter(int initialValue) {
            value = initialValue;
        }

        void increment() {
            value++;
        }
    }

    public static boolean run() {
        Counter counter = new Counter(40);
        counter.increment();
        counter.increment();

        return counter.value == 42;
    }
}
