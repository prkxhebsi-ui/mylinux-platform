#ifndef ART_RUNTIME_GC_HEAP_H_
#define ART_RUNTIME_GC_HEAP_H_

#include <cstddef>
#include <cstdint>

namespace art {
namespace gc {

class Heap {
 public:
  Heap() = default;
  Heap(const Heap&) = delete;
  Heap& operator=(const Heap&) = delete;
  virtual ~Heap() = default;

  virtual bool Initialize() = 0;
  virtual void CollectGarbage(bool clear_soft_references) = 0;
  virtual size_t GetBytesAllocated() const = 0;
  virtual size_t GetBytesAllocatedEver() const = 0;
  virtual uint64_t GetObjectsAllocated() const = 0;
};

}  // namespace gc
}  // namespace art

#endif  // ART_RUNTIME_GC_HEAP_H_
