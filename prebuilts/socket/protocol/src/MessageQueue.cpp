#include "MessageQueue.h"

namespace mylinux::socket::protocol {

MessageQueue::MessageQueue(size_t capacity)
    : capacity_(capacity) {}

bool MessageQueue::Push(const Message& message) {
    if (!message.Validate()) return false;

    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (closed_ || capacity_ == 0 || queue_.size() >= capacity_)
            return false;
        queue_.push_back(message);
    }
    condition_.notify_one();
    return true;
}

bool MessageQueue::TryPop(Message* output) {
    if (!output) return false;

    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) return false;

    *output = std::move(queue_.front());
    queue_.pop_front();
    return true;
}

bool MessageQueue::WaitPop(Message* output) {
    if (!output) return false;

    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this] { return closed_ || !queue_.empty(); });

    if (queue_.empty()) return false;

    *output = std::move(queue_.front());
    queue_.pop_front();
    return true;
}

void MessageQueue::Close() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        closed_ = true;
    }
    condition_.notify_all();
}

size_t MessageQueue::Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

bool MessageQueue::IsClosed() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return closed_;
}

} // namespace mylinux::socket::protocol
