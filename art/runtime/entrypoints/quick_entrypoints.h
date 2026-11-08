#ifndef ART_RUNTIME_ENTRYPOINTS_QUICK_ENTRYPOINTS_H_
#define ART_RUNTIME_ENTRYPOINTS_QUICK_ENTRYPOINTS_H_

#include <cstdint>

namespace art {
class ArtMethod;
class Thread;

namespace quick_entrypoints {

using VoidEntryPoint = void (*)(ArtMethod*, Thread*);
using IntEntryPoint = int32_t (*)(ArtMethod*, Thread*);
using LongEntryPoint = int64_t (*)(ArtMethod*, Thread*);

struct EntryPoints {
  VoidEntryPoint pDeliverException;
  VoidEntryPoint pThrowNullPointer;
  VoidEntryPoint pThrowStackOverflow;
  IntEntryPoint pIntegerDivide;
  LongEntryPoint pLongDivide;
};

}  // namespace quick_entrypoints
}  // namespace art

#endif  // ART_RUNTIME_ENTRYPOINTS_QUICK_ENTRYPOINTS_H_
