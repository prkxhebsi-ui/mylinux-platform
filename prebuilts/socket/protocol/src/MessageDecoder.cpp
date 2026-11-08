#include "MessageDecoder.h"
#include "MessageHeader.h"

namespace mylinux::socket::protocol {

bool MessageDecoder::DecodeFrame(const uint8_t* data,
                                 size_t length,
                                 Message* output,
                                 std::string* error) {
    if (!data || !output || length < kWireHeaderSize) {
        if (error) *error = "frame is too short";
        return false;
    }

    MessageHeader header;
    if (!DecodeHeader(data, length, &header, error)) return false;

    const size_t expected = kWireHeaderSize + header.payload_length;
    if (length != expected) {
        if (error) *error = "frame length does not match payload length";
        return false;
    }

    Message decoded;
    decoded.header = header;
    decoded.payload.assign(data + kWireHeaderSize, data + length);

    if (!decoded.Validate(error)) return false;
    *output = std::move(decoded);
    return true;
}

bool MessageDecoder::DecodeFrame(const std::vector<uint8_t>& data,
                                 Message* output,
                                 std::string* error) {
    return DecodeFrame(data.data(), data.size(), output, error);
}

} // namespace mylinux::socket::protocol
