#include <mylinux/art/bridge.h>

#include <mutex>

namespace {
std::mutex bridge_mutex;
art_mylinux_bridge_t registered_bridge = {};
bool bridge_available = false;
}

extern "C"
art_status_t art_mylinux_bridge_register(
    const art_mylinux_bridge_t *bridge)
{
    if (bridge == nullptr ||
        bridge->structure_size < sizeof(art_mylinux_bridge_t) ||
        bridge->abi_version != 1 ||
        bridge->allocate == nullptr ||
        bridge->deallocate == nullptr) {
        return ART_STATUS_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(bridge_mutex);

    if (bridge_available)
        return ART_STATUS_ALREADY_INITIALIZED;

    registered_bridge = *bridge;
    bridge_available = true;

    return ART_STATUS_OK;
}

extern "C"
const art_mylinux_bridge_t *art_mylinux_bridge_get(void)
{
    std::lock_guard<std::mutex> lock(bridge_mutex);

    if (!bridge_available)
        return nullptr;

    return &registered_bridge;
}
