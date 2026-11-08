#ifndef MYLINUX_SOCKET_PROTOCOL_MESSAGE_HEADER_H
#define MYLINUX_SOCKET_PROTOCOL_MESSAGE_HEADER_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace mylinux::socket::protocol {

constexpr uint32_t kMessageMagic = 0x4D4C5350U;
constexpr uint16_t kProtocolVersion = 1;
constexpr size_t kWireHeaderSize = 24;
constexpr uint32_t kMaximumPayloadSize = 1024U * 1024U;

enum class MessageType : uint16_t {
    Request = 1,
    Response = 2,
    Event = 3
};

struct MessageHeader {
    uint32_t magic = kMessageMagic;
    uint16_t version = kProtocolVersion;
    MessageType type = MessageType::Event;
    uint32_t flags = 0;
    uint64_t message_id = 0;
    uint32_t payload_length = 0;

    bool Validate(std::string* error = nullptr) const;
};

using WireHeader = std::array<uint8_t, kWireHeaderSize>;

bool EncodeHeader(const MessageHeader& header,
                  WireHeader* output,
                  std::string* error = nullptr);

bool DecodeHeader(const uint8_t* data,
                  size_t length,
                  MessageHeader* output,
                  std::string* error = nullptr);

} // namespace mylinux::socket::protocol

#endif
