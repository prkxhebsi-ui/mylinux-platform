#ifndef ART_RUNTIME_MONITOR_H_
#define ART_RUNTIME_MONITOR_H_

#include <condition_variable>
#include <mutex>

namespace art {

class Monitor {
 public:
  Monitor() = default;
  Monitor(const Monitor&) = delete;
  Monitor& operator=(const Monitor&) = delete;

  void Lock();
  void Unlock();
  void Wait();
  void NotifyOne();
  void NotifyAll();

 private:
  std::mutex mutex_;
  std::condition_variable condition_;
  bool locked_ = false;
};

}  // namespace art

#endif  // ART_RUNTIME_MONITOR_H_
