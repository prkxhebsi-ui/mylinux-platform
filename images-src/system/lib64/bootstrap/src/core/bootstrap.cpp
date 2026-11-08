#include "../include/bootstrap.h"

namespace mylinux {
namespace bootstrap {

// Initialize the bootstrap context
void initialize(BootstrapContext *context)
{
    if (context == nullptr)
        return;

    context->state = BOOTSTRAP_INITIALIZING;
    context->start_time = 0;
    context->component_count = 0;

    context->memory.base = 0;
    context->memory.size = 0;
    context->memory.available = 0;

    context->state = BOOTSTRAP_READY;
}

// Shutdown the bootstrap context
void shutdown(BootstrapContext *context)
{
    if (context == nullptr)
        return;

    context->state = BOOTSTRAP_UNINITIALIZED;
}

// Return a readable state name
const char *state_name(BootstrapState state)
{
    switch (state) {
        case BOOTSTRAP_UNINITIALIZED:
            return "uninitialized";

        case BOOTSTRAP_INITIALIZING:
            return "initializing";

        case BOOTSTRAP_READY:
            return "ready";

        case BOOTSTRAP_FAILED:
            return "failed";

        default:
            return "unknown";
    }
}

// Validate component metadata
bool validate_component(const ComponentInfo *component)
{
    if (component == nullptr)
        return false;

    if (component->name == nullptr || component->path == nullptr)
        return false;

    if (component->name[0] == '\0' || component->path[0] == '\0')
        return false;

    return true;
}

} // namespace bootstrap
} // namespace mylinux
