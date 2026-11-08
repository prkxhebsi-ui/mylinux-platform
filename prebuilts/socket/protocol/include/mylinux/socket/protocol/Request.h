#ifndef MYLINUX_SOCKET_PROTOCOL_REQUEST_H
#define MYLINUX_SOCKET_PROTOCOL_REQUEST_H

#include "Message.h"

namespace mylinux::socket::protocol {

struct Request {
    uint64_t id = 0;
    std::vector<uint8_t> payload;

    Message ToMessage() const;
    static bool FromMessage(const Message& message,
                            Request* output,
                            std::string* error = nullptr);
};

} // namespace mylinux::socket::protocol

#endif
