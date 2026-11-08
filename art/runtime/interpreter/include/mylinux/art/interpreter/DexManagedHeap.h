#ifndef MYLINUX_ART_DEX_MANAGED_HEAP_H
#define MYLINUX_ART_DEX_MANAGED_HEAP_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace mylinux {
namespace art {
namespace interpreter {

using ObjectRef = uint32_t;

enum class HeapObjectKind {
    INSTANCE,
    INTEGER_ARRAY
};

struct HeapStats {
    size_t object_count = 0;
    size_t used_bytes = 0;
    size_t maximum_bytes = 0;
};

class DexManagedHeap {
public:
    explicit DexManagedHeap(size_t maximum_bytes = 1024 * 1024);

    ObjectRef AllocateObject(
        uint32_t class_index,
        uint32_t field_count
    );

    ObjectRef AllocateIntArray(uint32_t length);

    bool GetField(
        ObjectRef object,
        uint32_t field_index,
        int32_t* value
    );

    bool SetField(
        ObjectRef object,
        uint32_t field_index,
        int32_t value
    );

    bool GetArrayElement(
        ObjectRef array,
        uint32_t index,
        int32_t* value
    );

    bool SetArrayElement(
        ObjectRef array,
        uint32_t index,
        int32_t value
    );

    bool GetObjectClass(
        ObjectRef object,
        uint32_t* class_index
    );

    bool GetArrayLength(
        ObjectRef array,
        uint32_t* length
    );

    HeapStats GetStats() const;

    const std::string& GetError() const;

    void Clear();

private:
    struct HeapObject {
        HeapObjectKind kind;
        uint32_t class_index = 0;
        std::vector<int32_t> values;
        size_t accounted_bytes = 0;
    };

    std::vector<std::unique_ptr<HeapObject>> objects_;
    size_t maximum_bytes_;
    size_t used_bytes_;
    std::string error_;

    HeapObject* Find(ObjectRef ref);
    const HeapObject* Find(ObjectRef ref) const;

    bool Reserve(size_t bytes);
    void SetError(const char* message);
};

} // namespace interpreter
} // namespace art
} // namespace mylinux

#endif
