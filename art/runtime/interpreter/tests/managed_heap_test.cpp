#include "mylinux/art/interpreter/DexManagedHeap.h"

#include <cstdio>

using mylinux::art::interpreter::DexManagedHeap;
using mylinux::art::interpreter::ObjectRef;

static int Fail(const char* message) {
    std::fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

int main() {
    DexManagedHeap heap(64 * 1024);

    ObjectRef object = heap.AllocateObject(42, 3);
    if (!object) return Fail(heap.GetError().c_str());

    if (!heap.SetField(object, 0, 123))
        return Fail(heap.GetError().c_str());

    if (!heap.SetField(object, 1, 456))
        return Fail(heap.GetError().c_str());

    int32_t value = 0;

    if (!heap.GetField(object, 0, &value) || value != 123)
        return Fail("object field 0 did not retain its value");

    if (!heap.GetField(object, 1, &value) || value != 456)
        return Fail("object field 1 did not retain its value");

    uint32_t class_index = 0;

    if (!heap.GetObjectClass(object, &class_index) ||
        class_index != 42)
        return Fail("object class ID mismatch");

    ObjectRef array = heap.AllocateIntArray(4);
    if (!array) return Fail(heap.GetError().c_str());

    if (!heap.SetArrayElement(array, 0, 10) ||
        !heap.SetArrayElement(array, 1, 20) ||
        !heap.SetArrayElement(array, 2, 30) ||
        !heap.SetArrayElement(array, 3, 40))
        return Fail(heap.GetError().c_str());

    if (!heap.GetArrayElement(array, 2, &value) || value != 30)
        return Fail("array element did not retain its value");

    uint32_t length = 0;

    if (!heap.GetArrayLength(array, &length) || length != 4)
        return Fail("array length mismatch");

    if (heap.GetArrayElement(array, 99, &value))
        return Fail("out-of-bounds array access was accepted");

    auto stats = heap.GetStats();

    if (stats.object_count != 2 || stats.used_bytes == 0)
        return Fail("heap statistics are incorrect");

    std::printf("Managed heap test passed\n");
    std::printf("Objects: %zu\n", stats.object_count);
    std::printf("Heap bytes: %zu / %zu\n",
                stats.used_bytes, stats.maximum_bytes);

    heap.Clear();

    if (heap.GetStats().object_count != 0)
        return Fail("heap clear failed");

    std::puts("Heap clear test passed");
    return 0;
}
