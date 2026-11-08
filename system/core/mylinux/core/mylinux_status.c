#include "mylinux_status.h"

const char *mylinux_status_string(mylinux_status_t status)
{
    switch (status) {
    case MYLINUX_STATUS_OK:
        return "OK";

    case MYLINUX_STATUS_ERROR:
        return "General error";

    case MYLINUX_STATUS_INVALID_ARGUMENT:
        return "Invalid argument";

    case MYLINUX_STATUS_NOT_FOUND:
        return "Not found";

    case MYLINUX_STATUS_PERMISSION_DENIED:
        return "Permission denied";

    case MYLINUX_STATUS_OUT_OF_MEMORY:
        return "Out of memory";

    case MYLINUX_STATUS_NOT_SUPPORTED:
        return "Not supported";

    default:
        return "Unknown status";
    }
}
