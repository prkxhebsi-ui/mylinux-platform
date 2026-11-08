#ifndef MYLINUX_SOCKET_PROTOCOL_MESSAGE_DECODER_H
#define MYLINUX_SOCKET_PROTOCOL_MESSAGE_DECODER_H

#include "Message.h"
#include <cstdint>
#include <string>
#include <vector>

namespace mylinux::socket::protocol {

class MessageDecoder {
public:
    static bool DecodeFrame(const uint8_t* data,
                            size_t length,
                            Message* output,
                            std::string* error = nullptr);

    static bool DecodeFrame(const std::vector<uint8_t>& data,
                            Message* output,
                            std::string* error = nullptr);
};

} // namespace mylinux::socket::protocol

#endif
