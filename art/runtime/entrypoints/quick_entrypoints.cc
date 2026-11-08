#include "runtime/entrypoints/quick_entrypoints.h"

namespace art {
namespace quick_entrypoints {

static void DeliverExceptionPlaceholder(ArtMethod*, Thread*) {}
static void ThrowNullPointerPlaceholder(ArtMethod*, Thread*) {}
static void ThrowStackOverflowPlaceholder(ArtMethod*, Thread*) {}
static int32_t IntegerDividePlaceholder(ArtMethod*, Thread*) { return 0; }
static int64_t LongDividePlaceholder(ArtMethod*, Thread*) { return 0; }

EntryPoints CreateEntryPoints() {
  return {
      DeliverExceptionPlaceholder,
      ThrowNullPointerPlaceholder,
      ThrowStackOverflowPlaceholder,
      IntegerDividePlaceholder,
      LongDividePlaceholder,
  };
}

}  // namespace quick_entrypoints
}  // namespace art
