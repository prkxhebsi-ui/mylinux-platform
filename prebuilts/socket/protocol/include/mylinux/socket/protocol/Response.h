#ifndef MYLINUX_SOCKET_PROTOCOL_RESPONSE_H
#define MYLINUX_SOCKET_PROTOCOL_RESPONSE_H

#include "Message.h"

namespace mylinux::socket::protocol {

struct Response {
    uint64_t id = 0;
    uint32_t status = 0;
    std::vector<uint8_t> payload;

    Message ToMessage() const;
    static bool FromMessage(const Message& message,
                            Response* output,
                            std::string* error = nullptr);
};

} // namespace mylinux::socket::protocol

#endif
