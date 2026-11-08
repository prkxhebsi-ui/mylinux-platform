#include "Response.h"

namespace mylinux::socket::protocol {

Message Response::ToMessage() const {
    Message message;
    message.header.type = MessageType::Response;
    message.header.message_id = id;
    message.header.payload_length =
        static_cast<uint32_t>(sizeof(status) + payload.size());

    message.payload.reserve(message.header.payload_length);

    message.payload.push_back(static_cast<uint8_t>(status >> 24));
    message.payload.push_back(static_cast<uint8_t>(status >> 16));
    message.payload.push_back(static_cast<uint8_t>(status >> 8));
    message.payload.push_back(static_cast<uint8_t>(status));

    message.payload.insert(message.payload.end(),
                           payload.begin(), payload.end());
    return message;
}

bool Response::FromMessage(const Message& message,
                           Response* output,
                           std::string* error) {
    if (!output) {
        if (error) *error = "null response output";
        return false;
    }
    if (!message.Validate(error)) return false;
    if (message.header.type != MessageType::Response) {
        if (error) *error = "message is not a response";
        return false;
    }
    if (message.payload.size() < 4) {
        if (error) *error = "response has no status field";
        return false;
    }

    output->id = message.header.message_id;
    output->status =
        (static_cast<uint32_t>(message.payload[0]) << 24) |
        (static_cast<uint32_t>(message.payload[1]) << 16) |
        (static_cast<uint32_t>(message.payload[2]) << 8) |
        static_cast<uint32_t>(message.payload[3]);

    output->payload.assign(message.payload.begin() + 4,
                           message.payload.end());
    return true;
}

} // namespace mylinux::socket::protocol
