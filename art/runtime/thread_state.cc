#include "runtime/thread_state.h"

namespace art {

const char* ThreadStateToString(ThreadState state) {
  switch (state) {
    case ThreadState::kStarting: return "starting";
    case ThreadState::kRunnable: return "runnable";
    case ThreadState::kNative: return "native";
    case ThreadState::kSuspended: return "suspended";
    case ThreadState::kWaiting: return "waiting";
    case ThreadState::kTerminated: return "terminated";
  }
  return "unknown";
}

}  // namespace art
