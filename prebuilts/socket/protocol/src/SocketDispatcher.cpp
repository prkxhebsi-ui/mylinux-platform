#include "SocketDispatcher.h"

namespace mylinux::socket::protocol {

bool SocketDispatcher::Register(uint32_t command, Handler handler) {
    if (!handler) return false;

    std::lock_guard<std::mutex> lock(mutex_);
    return handlers_.emplace(command, std::move(handler)).second;
}

bool SocketDispatcher::Unregister(uint32_t command) {
    std::lock_guard<std::mutex> lock(mutex_);
    return handlers_.erase(command) != 0;
}

bool SocketDispatcher::Dispatch(const Message& incoming,
                                Message* outgoing,
                                std::string* error) const {
    if (!outgoing) {
        if (error) *error = "null dispatch output";
        return false;
    }

    Request request;
    if (!Request::FromMessage(incoming, &request, error)) return false;

    // The first four request-payload bytes contain the command ID.
    if (request.payload.size() < 4) {
        if (error) *error = "request is missing its command ID";
        return false;
    }

    const uint32_t command =
        (static_cast<uint32_t>(request.payload[0]) << 24) |
        (static_cast<uint32_t>(request.payload[1]) << 16) |
        (static_cast<uint32_t>(request.payload[2]) << 8) |
        static_cast<uint32_t>(request.payload[3]);

    Handler handler;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = handlers_.find(command);
        if (it == handlers_.end()) {
            if (error) *error = "no handler registered for command";
            return false;
        }
        handler = it->second;
    }

    request.payload.erase(request.payload.begin(),
                          request.payload.begin() + 4);

    Response response = handler(request);
    response.id = request.id;
    Message result = response.ToMessage();

    if (!result.Validate(error)) return false;
    *outgoing = std::move(result);
    return true;
}

} // namespace mylinux::socket::protocol
