#include "runtime/monitor.h"

namespace art {

void Monitor::Lock() {
  mutex_.lock();
  locked_ = true;
}

void Monitor::Unlock() {
  locked_ = false;
  mutex_.unlock();
}

void Monitor::Wait() {
  std::unique_lock<std::mutex> lock(mutex_, std::adopt_lock);
  locked_ = false;
  condition_.wait(lock);
  locked_ = true;
  lock.release();
}

void Monitor::NotifyOne() {
  condition_.notify_one();
}

void Monitor::NotifyAll() {
  condition_.notify_all();
}

}  // namespace art
