#include <stdio.h>
#include <sys/utsname.h>

int main(void)
{
    struct utsname info;

    if (uname(&info) != 0) {
        perror("uname");
        return 1;
    }

    printf("System:   %s\n", info.sysname);
    printf("Node:     %s\n", info.nodename);
    printf("Release:  %s\n", info.release);
    printf("Version:  %s\n", info.version);
    printf("Machine:  %s\n", info.machine);

    return 0;
}
