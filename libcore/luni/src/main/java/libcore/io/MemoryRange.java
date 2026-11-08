package libcore.io;

/** Represents a validated range within an array. */
public final class MemoryRange {
    private final int offset;
    private final int length;

    public MemoryRange(int arrayLength, int offset, int length) {
        if (arrayLength < 0 || offset < 0 || length < 0 ||
                offset > arrayLength || length > arrayLength - offset) {
            throw new IndexOutOfBoundsException("Invalid memory range");
        }

        this.offset = offset;
        this.length = length;
    }

    public int offset() {
        return offset;
    }

    public int length() {
        return length;
    }

    public int endExclusive() {
        return offset + length;
    }

    public boolean contains(int index) {
        return index >= offset && index < endExclusive();
    }

    public boolean isEmpty() {
        return length == 0;
    }
}
