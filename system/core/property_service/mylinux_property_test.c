#include <stdio.h>

#include "mylinux_property.h"

int main(void)
{
    if (mylinux_property_validate_name("mylinux.platform") !=
        MYLINUX_PROPERTY_OK) {
        return 1;
    }

    if (mylinux_property_validate_name("") !=
        MYLINUX_PROPERTY_INVALID_ARGUMENT) {
        return 1;
    }

    if (mylinux_property_validate_name("mylinux..platform") !=
        MYLINUX_PROPERTY_INVALID_ARGUMENT) {
        return 1;
    }

    if (mylinux_property_validate_name("mylinux platform") !=
        MYLINUX_PROPERTY_INVALID_ARGUMENT) {
        return 1;
    }

    puts("MyLinux property validation: PASS");
    return 0;
}
