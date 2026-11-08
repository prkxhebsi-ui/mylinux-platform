#include <mylinux/art/runtime.h>
#include <runtime_features.h>
#include <art_config.h>

#include <mutex>

namespace {

std::mutex runtime_mutex;

art_runtime_info_t runtime_info = {
    MYLINUX_ART_VERSION_MAJOR,
    MYLINUX_ART_VERSION_MINOR,
    MYLINUX_ART_VERSION_PATCH,
    ART_FEATURE_METADATA |
    ART_FEATURE_RUNTIME_BRIDGE |
    ART_FEATURE_DEX_METADATA |
    ART_FEATURE_LIBRARY_LOADER,
    ART_RUNTIME_COLD
};

}

extern "C"
art_status_t art_runtime_initialize(void)
{
    std::lock_guard<std::mutex> lock(runtime_mutex);

    if (runtime_info.state == ART_RUNTIME_READY)
        return ART_STATUS_ALREADY_INITIALIZED;

    if (runtime_info.state != ART_RUNTIME_COLD)
        return ART_STATUS_INTERNAL_ERROR;

    runtime_info.state = ART_RUNTIME_INITIALIZING;

    runtime_info.state = ART_RUNTIME_READY;
    return ART_STATUS_OK;
}

extern "C"
art_status_t art_runtime_shutdown(void)
{
    std::lock_guard<std::mutex> lock(runtime_mutex);

    if (runtime_info.state != ART_RUNTIME_READY)
        return ART_STATUS_NOT_INITIALIZED;

    runtime_info.state = ART_RUNTIME_SHUTTING_DOWN;
    runtime_info.state = ART_RUNTIME_COLD;

    return ART_STATUS_OK;
}

extern "C"
art_runtime_state_t art_runtime_get_state(void)
{
    std::lock_guard<std::mutex> lock(runtime_mutex);
    return runtime_info.state;
}

extern "C"
art_status_t art_runtime_get_info(art_runtime_info_t *info)
{
    if (info == nullptr)
        return ART_STATUS_INVALID_ARGUMENT;

    std::lock_guard<std::mutex> lock(runtime_mutex);
    *info = runtime_info;

    return ART_STATUS_OK;
}
