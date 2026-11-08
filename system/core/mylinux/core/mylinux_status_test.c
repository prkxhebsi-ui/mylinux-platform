#include <stdio.h>
#include "mylinux_status.h"

int main(void)
{
    mylinux_status_t status = MYLINUX_STATUS_PERMISSION_DENIED;

    printf("MyLinux status: %s\n",
           mylinux_status_string(status));

    printf("Success status: %s\n",
           mylinux_status_string(MYLINUX_STATUS_OK));

    printf("Unknown status: %s\n",
           mylinux_status_string((mylinux_status_t)999));

    return 0;
}
