#ifndef ART_RUNTIME_THREAD_STATE_H_
#define ART_RUNTIME_THREAD_STATE_H_

#include <cstdint>

namespace art {

enum class ThreadState : uint8_t {
  kStarting,
  kRunnable,
  kNative,
  kSuspended,
  kWaiting,
  kTerminated,
};

const char* ThreadStateToString(ThreadState state);

}  // namespace art

#endif  // ART_RUNTIME_THREAD_STATE_H_
