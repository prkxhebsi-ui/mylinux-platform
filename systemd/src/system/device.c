#include "device.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <stdio.h>

int sd_create_basic_devices(void)
{
    int errors = 0;

    if (mknod("/dev/null", S_IFCHR | 0666, makedev(1, 3)) < 0
        && errno != EEXIST) {
        perror("systemd: mknod /dev/null");
        errors++;
    }

    if (mknod("/dev/zero", S_IFCHR | 0666, makedev(1, 5)) < 0
        && errno != EEXIST) {
        perror("systemd: mknod /dev/zero");
        errors++;
    }

    if (mknod("/dev/full", S_IFCHR | 0666, makedev(1, 7)) < 0
        && errno != EEXIST) {
        perror("systemd: mknod /dev/full");
        errors++;
    }

    if (mknod("/dev/console", S_IFCHR | 0600, makedev(5, 1)) < 0
        && errno != EEXIST) {
        perror("systemd: mknod /dev/console");
        errors++;
    }

    if (mknod("/dev/tty", S_IFCHR | 0666, makedev(5, 0)) < 0
        && errno != EEXIST) {
        perror("systemd: mknod /dev/tty");
        errors++;
    }

    if (mknod("/dev/kmsg", S_IFCHR | 0600, makedev(1, 11)) < 0
        && errno != EEXIST) {
        perror("systemd: mknod /dev/kmsg");
        errors++;
    }

    return errors ? 1 : 0;
}
