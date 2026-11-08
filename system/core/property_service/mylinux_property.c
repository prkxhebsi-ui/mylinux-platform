#include "mylinux_property.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

mylinux_property_status_t
mylinux_property_validate_name(const char *name)
{
    size_t i;
    size_t length;

    if (name == NULL || name[0] == '\0') {
        return MYLINUX_PROPERTY_INVALID_ARGUMENT;
    }

    length = strlen(name);

    if (length >= MYLINUX_PROPERTY_NAME_MAX) {
        return MYLINUX_PROPERTY_INVALID_ARGUMENT;
    }

    if (name[0] == '.' || name[length - 1] == '.') {
        return MYLINUX_PROPERTY_INVALID_ARGUMENT;
    }

    for (i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)name[i];

        if (!(isalnum(ch) || ch == '.' || ch == '_' || ch == '-')) {
            return MYLINUX_PROPERTY_INVALID_ARGUMENT;
        }

        if (ch == '.' && i > 0 && name[i - 1] == '.') {
            return MYLINUX_PROPERTY_INVALID_ARGUMENT;
        }
    }

    return MYLINUX_PROPERTY_OK;
}
