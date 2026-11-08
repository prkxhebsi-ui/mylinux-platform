#include "mylinux/art/interpreter/DexManagedHeap.h"

#include <limits>
#include <new>
#include <utility>

namespace mylinux {
namespace art {
namespace interpreter {

DexManagedHeap::DexManagedHeap(size_t maximum_bytes)
    : maximum_bytes_(maximum_bytes),
      used_bytes_(0) {
}

void DexManagedHeap::SetError(const char* message) {
    error_ = message;
}

bool DexManagedHeap::Reserve(size_t bytes) {
    if (bytes > maximum_bytes_ ||
        used_bytes_ > maximum_bytes_ - bytes) {
        SetError("managed heap memory limit exceeded");
        return false;
    }

    used_bytes_ += bytes;
    return true;
}

DexManagedHeap::HeapObject* DexManagedHeap::Find(ObjectRef ref) {
    if (ref == 0 || ref > objects_.size()) {
        SetError("invalid object reference");
        return nullptr;
    }

    return objects_[ref - 1].get();
}

const DexManagedHeap::HeapObject*
DexManagedHeap::Find(ObjectRef ref) const {
    if (ref == 0 || ref > objects_.size()) {
        return nullptr;
    }

    return objects_[ref - 1].get();
}

ObjectRef DexManagedHeap::AllocateObject(
    uint32_t class_index,
    uint32_t field_count
) {
    error_.clear();

    if (field_count >
        (std::numeric_limits<size_t>::max() -
         sizeof(HeapObject)) / sizeof(int32_t)) {
        SetError("object size overflow");
        return 0;
    }

    const size_t bytes =
        sizeof(HeapObject) +
        static_cast<size_t>(field_count) * sizeof(int32_t);

    if (objects_.size() >=
        std::numeric_limits<ObjectRef>::max()) {
        SetError("object reference table is full");
        return 0;
    }

    if (!Reserve(bytes)) {
        return 0;
    }

    try {
        std::unique_ptr<HeapObject> object(new HeapObject());

        object->kind = HeapObjectKind::INSTANCE;
        object->class_index = class_index;
        object->values.resize(field_count, 0);
        object->accounted_bytes = bytes;

        objects_.push_back(std::move(object));
    } catch (const std::bad_alloc&) {
        used_bytes_ -= bytes;
        SetError("host memory allocation failed");
        return 0;
    }

    return static_cast<ObjectRef>(objects_.size());
}

ObjectRef DexManagedHeap::AllocateIntArray(uint32_t length) {
    error_.clear();

    if (length >
        (std::numeric_limits<size_t>::max() -
         sizeof(HeapObject)) / sizeof(int32_t)) {
        SetError("array size overflow");
        return 0;
    }

    const size_t bytes =
        sizeof(HeapObject) +
        static_cast<size_t>(length) * sizeof(int32_t);

    if (objects_.size() >=
        std::numeric_limits<ObjectRef>::max()) {
        SetError("object reference table is full");
        return 0;
    }

    if (!Reserve(bytes)) {
        return 0;
    }

    try {
        std::unique_ptr<HeapObject> object(new HeapObject());

        object->kind = HeapObjectKind::INTEGER_ARRAY;
        object->values.resize(length, 0);
        object->accounted_bytes = bytes;

        objects_.push_back(std::move(object));
    } catch (const std::bad_alloc&) {
        used_bytes_ -= bytes;
        SetError("host memory allocation failed");
        return 0;
    }

    return static_cast<ObjectRef>(objects_.size());
}

bool DexManagedHeap::GetField(
    ObjectRef ref,
    uint32_t field_index,
    int32_t* value
) {
    error_.clear();

    if (value == nullptr) {
        SetError("null output pointer");
        return false;
    }

    HeapObject* object = Find(ref);
    if (!object) return false;

    if (object->kind != HeapObjectKind::INSTANCE) {
        SetError("reference is not an object instance");
        return false;
    }

    if (field_index >= object->values.size()) {
        SetError("instance field index out of bounds");
        return false;
    }

    *value = object->values[field_index];
    return true;
}

bool DexManagedHeap::SetField(
    ObjectRef ref,
    uint32_t field_index,
    int32_t value
) {
    error_.clear();

    HeapObject* object = Find(ref);
    if (!object) return false;

    if (object->kind != HeapObjectKind::INSTANCE) {
        SetError("reference is not an object instance");
        return false;
    }

    if (field_index >= object->values.size()) {
        SetError("instance field index out of bounds");
        return false;
    }

    object->values[field_index] = value;
    return true;
}

bool DexManagedHeap::GetArrayElement(
    ObjectRef ref,
    uint32_t index,
    int32_t* value
) {
    error_.clear();

    if (value == nullptr) {
        SetError("null output pointer");
        return false;
    }

    HeapObject* object = Find(ref);
    if (!object) return false;

    if (object->kind != HeapObjectKind::INTEGER_ARRAY) {
        SetError("reference is not an integer array");
        return false;
    }

    if (index >= object->values.size()) {
        SetError("array index out of bounds");
        return false;
    }

    *value = object->values[index];
    return true;
}

bool DexManagedHeap::SetArrayElement(
    ObjectRef ref,
    uint32_t index,
    int32_t value
) {
    error_.clear();

    HeapObject* object = Find(ref);
    if (!object) return false;

    if (object->kind != HeapObjectKind::INTEGER_ARRAY) {
        SetError("reference is not an integer array");
        return false;
    }

    if (index >= object->values.size()) {
        SetError("array index out of bounds");
        return false;
    }

    object->values[index] = value;
    return true;
}

bool DexManagedHeap::GetObjectClass(
    ObjectRef ref,
    uint32_t* class_index
) {
    error_.clear();

    if (class_index == nullptr) {
        SetError("null output pointer");
        return false;
    }

    HeapObject* object = Find(ref);
    if (!object) return false;

    if (object->kind != HeapObjectKind::INSTANCE) {
        SetError("reference is not an object instance");
        return false;
    }

    *class_index = object->class_index;
    return true;
}

bool DexManagedHeap::GetArrayLength(
    ObjectRef ref,
    uint32_t* length
) {
    error_.clear();

    if (length == nullptr) {
        SetError("null output pointer");
        return false;
    }

    HeapObject* object = Find(ref);
    if (!object) return false;

    if (object->kind != HeapObjectKind::INTEGER_ARRAY) {
        SetError("reference is not an integer array");
        return false;
    }

    *length = static_cast<uint32_t>(object->values.size());
    return true;
}

HeapStats DexManagedHeap::GetStats() const {
    HeapStats stats;
    stats.object_count = objects_.size();
    stats.used_bytes = used_bytes_;
    stats.maximum_bytes = maximum_bytes_;
    return stats;
}

const std::string& DexManagedHeap::GetError() const {
    return error_;
}

void DexManagedHeap::Clear() {
    objects_.clear();
    used_bytes_ = 0;
    error_.clear();
}

} // namespace interpreter
} // namespace art
} // namespace mylinux
