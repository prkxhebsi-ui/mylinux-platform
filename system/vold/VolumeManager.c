#include <stdio.h>
#include "mylinux_vold.h"

void vold_print_version(void)
{
    puts("MyLinux vold prototype 0.1.0");
}

void vold_list_volumes(void)
{
    puts("Managed volumes: 0");
    puts("No real devices are mounted or modified by this prototype.");
}
