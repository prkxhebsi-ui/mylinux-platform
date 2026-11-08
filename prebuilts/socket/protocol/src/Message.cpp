#include "Message.h"

namespace mylinux::socket::protocol {

bool Message::Validate(std::string* error) const {
    if (!header.Validate(error)) return false;

    if (payload.size() != header.payload_length) {
        if (error) *error = "payload length does not match header";
        return false;
    }
    return true;
}

} // namespace mylinux::socket::protocol
