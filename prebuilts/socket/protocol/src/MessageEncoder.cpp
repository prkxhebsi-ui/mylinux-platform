#include "MessageEncoder.h"
#include "MessageHeader.h"

namespace mylinux::socket::protocol {

bool MessageEncoder::Encode(const Message& message,
                            std::vector<uint8_t>* output,
                            std::string* error) {
    if (!output) {
        if (error) *error = "null encoded output";
        return false;
    }
    if (!message.Validate(error)) return false;

    WireHeader header{};
    if (!EncodeHeader(message.header, &header, error)) return false;

    std::vector<uint8_t> frame;
    frame.reserve(kWireHeaderSize + message.payload.size());
    frame.insert(frame.end(), header.begin(), header.end());
    frame.insert(frame.end(), message.payload.begin(), message.payload.end());

    *output = std::move(frame);
    return true;
}

} // namespace mylinux::socket::protocol
