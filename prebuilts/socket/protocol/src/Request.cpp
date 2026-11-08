#include "Request.h"

namespace mylinux::socket::protocol {

Message Request::ToMessage() const {
    Message message;
    message.header.type = MessageType::Request;
    message.header.message_id = id;
    message.header.payload_length = static_cast<uint32_t>(payload.size());
    message.payload = payload;
    return message;
}

bool Request::FromMessage(const Message& message,
                          Request* output,
                          std::string* error) {
    if (!output) {
        if (error) *error = "null request output";
        return false;
    }
    if (!message.Validate(error)) return false;
    if (message.header.type != MessageType::Request) {
        if (error) *error = "message is not a request";
        return false;
    }

    output->id = message.header.message_id;
    output->payload = message.payload;
    return true;
}

} // namespace mylinux::socket::protocol
