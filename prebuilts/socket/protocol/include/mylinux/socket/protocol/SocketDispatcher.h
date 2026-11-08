#ifndef MYLINUX_SOCKET_PROTOCOL_SOCKET_DISPATCHER_H
#define MYLINUX_SOCKET_PROTOCOL_SOCKET_DISPATCHER_H

#include "Request.h"
#include "Response.h"
#include <functional>
#include <mutex>
#include <unordered_map>

namespace mylinux::socket::protocol {

class SocketDispatcher {
public:
    using Handler = std::function<Response(const Request&)>;

    bool Register(uint32_t command, Handler handler);
    bool Unregister(uint32_t command);
    bool Dispatch(const Message& incoming,
                  Message* outgoing,
                  std::string* error = nullptr) const;

private:
    mutable std::mutex mutex_;
    std::unordered_map<uint32_t, Handler> handlers_;
};

} // namespace mylinux::socket::protocol

#endif
