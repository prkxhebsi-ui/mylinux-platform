#include <mylinux/art/status.h>

extern "C"
const char *art_status_string(art_status_t status)
{
    switch (status) {
    case ART_STATUS_OK:
        return "success";
    case ART_STATUS_INVALID_ARGUMENT:
        return "invalid argument";
    case ART_STATUS_NOT_INITIALIZED:
        return "runtime not initialized";
    case ART_STATUS_ALREADY_INITIALIZED:
        return "runtime already initialized";
    case ART_STATUS_OUT_OF_MEMORY:
        return "out of memory";
    case ART_STATUS_IO_ERROR:
        return "I/O error";
    case ART_STATUS_NOT_SUPPORTED:
        return "operation not supported";
    case ART_STATUS_INTERNAL_ERROR:
        return "internal runtime error";
    default:
        return "unknown runtime status";
    }
}
