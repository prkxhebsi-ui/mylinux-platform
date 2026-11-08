#include "MessageHeader.h"

namespace mylinux::socket::protocol {
namespace {

void Put16(uint8_t* p, uint16_t v) {
    p[0] = static_cast<uint8_t>(v >> 8);
    p[1] = static_cast<uint8_t>(v);
}

void Put32(uint8_t* p, uint32_t v) {
    p[0] = static_cast<uint8_t>(v >> 24);
    p[1] = static_cast<uint8_t>(v >> 16);
    p[2] = static_cast<uint8_t>(v >> 8);
    p[3] = static_cast<uint8_t>(v);
}

void Put64(uint8_t* p, uint64_t v) {
    for (int i = 7; i >= 0; --i) {
        p[i] = static_cast<uint8_t>(v);
        v >>= 8;
    }
}

uint16_t Get16(const uint8_t* p) {
    return static_cast<uint16_t>(
        (static_cast<uint16_t>(p[0]) << 8) | p[1]);
}

uint32_t Get32(const uint8_t* p) {
    return (static_cast<uint32_t>(p[0]) << 24) |
           (static_cast<uint32_t>(p[1]) << 16) |
           (static_cast<uint32_t>(p[2]) << 8) |
           static_cast<uint32_t>(p[3]);
}

uint64_t Get64(const uint8_t* p) {
    uint64_t value = 0;
    for (int i = 0; i < 8; ++i)
        value = (value << 8) | p[i];
    return value;
}

} // namespace

bool MessageHeader::Validate(std::string* error) const {
    auto fail = [error](const char* reason) {
        if (error) *error = reason;
        return false;
    };

    if (magic != kMessageMagic) return fail("invalid message magic");
    if (version != kProtocolVersion) return fail("unsupported protocol version");

    const auto t = static_cast<uint16_t>(type);
    if (t < 1 || t > 3) return fail("invalid message type");

    if (message_id == 0) return fail("message ID must not be zero");
    if (payload_length > kMaximumPayloadSize)
        return fail("payload exceeds maximum size");

    return true;
}

bool EncodeHeader(const MessageHeader& h,
                  WireHeader* output,
                  std::string* error) {
    if (!output) {
        if (error) *error = "null header output";
        return false;
    }
    if (!h.Validate(error)) return false;

    Put32(output->data(), h.magic);
    Put16(output->data() + 4, h.version);
    Put16(output->data() + 6, static_cast<uint16_t>(h.type));
    Put32(output->data() + 8, h.flags);
    Put64(output->data() + 12, h.message_id);
    Put32(output->data() + 20, h.payload_length);
    return true;
}

bool DecodeHeader(const uint8_t* data,
                  size_t length,
                  MessageHeader* output,
                  std::string* error) {
    if (!data || !output || length < kWireHeaderSize) {
        if (error) *error = "incomplete message header";
        return false;
    }

    MessageHeader h;
    h.magic = Get32(data);
    h.version = Get16(data + 4);
    h.type = static_cast<MessageType>(Get16(data + 6));
    h.flags = Get32(data + 8);
    h.message_id = Get64(data + 12);
    h.payload_length = Get32(data + 20);

    if (!h.Validate(error)) return false;
    *output = h;
    return true;
}

} // namespace mylinux::socket::protocol
