#ifndef MYLINUX_SOCKET_PROTOCOL_MESSAGE_QUEUE_H
#define MYLINUX_SOCKET_PROTOCOL_MESSAGE_QUEUE_H

#include "Message.h"
#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>

namespace mylinux::socket::protocol {

class MessageQueue {
public:
    explicit MessageQueue(size_t capacity = 256);

    bool Push(const Message& message);
    bool TryPop(Message* output);
    bool WaitPop(Message* output);
    void Close();
    size_t Size() const;
    bool IsClosed() const;

private:
    const size_t capacity_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    std::deque<Message> queue_;
    bool closed_ = false;
};

} // namespace mylinux::socket::protocol

#endif
