#ifndef MYLINUX_SOCKET_PROTOCOL_MESSAGE_H
#define MYLINUX_SOCKET_PROTOCOL_MESSAGE_H

#include "MessageHeader.h"
#include <cstdint>
#include <string>
#include <vector>

namespace mylinux::socket::protocol {

struct Message {
    MessageHeader header;
    std::vector<uint8_t> payload;

    bool Validate(std::string* error = nullptr) const;
};

} // namespace mylinux::socket::protocol

#endif
