#ifndef MYLINUX_SOCKET_PROTOCOL_MESSAGE_ENCODER_H
#define MYLINUX_SOCKET_PROTOCOL_MESSAGE_ENCODER_H

#include "Message.h"
#include <cstdint>
#include <string>
#include <vector>

namespace mylinux::socket::protocol {

class MessageEncoder {
public:
    static bool Encode(const Message& message,
                       std::vector<uint8_t>* output,
                       std::string* error = nullptr);
};

} // namespace mylinux::socket::protocol

#endif
