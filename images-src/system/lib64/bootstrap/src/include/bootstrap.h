#ifndef MYLINUX_BOOTSTRAP_H
#define MYLINUX_BOOTSTRAP_H

#include <stdint.h>
#include <stddef.h>

// MyLinux bootstrap namespace
namespace mylinux {
namespace bootstrap {

// Bootstrap execution states
enum BootstrapState {
    BOOTSTRAP_UNINITIALIZED = 0,
    BOOTSTRAP_INITIALIZING,
    BOOTSTRAP_READY,
    BOOTSTRAP_FAILED
};

// Bootstrap component types
typedef enum {
    COMPONENT_UNKNOWN = 0,
    COMPONENT_RUNTIME,
    COMPONENT_LINKER,
    COMPONENT_LIBRARY,
    COMPONENT_FRAMEWORK
} ComponentType;

// Bootstrap memory information
struct MemoryInfo {
    uint64_t base;
    uint64_t size;
    uint64_t available;
};

// Bootstrap component information
struct ComponentInfo {
    const char *name;
    const char *path;
    ComponentType type;
    uint64_t flags;
};

// Bootstrap status
struct BootstrapContext {
    BootstrapState state;
    uint64_t start_time;
    uint64_t component_count;
    MemoryInfo memory;
};

// Function declarations
void initialize(BootstrapContext *context);
void shutdown(BootstrapContext *context);
const char *state_name(BootstrapState state);
bool validate_component(const ComponentInfo *component);

} // namespace bootstrap
} // namespace mylinux

#endif // MYLINUX_BOOTSTRAP_H
