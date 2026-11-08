#include "mount.h"

#include <sys/mount.h>
#include <errno.h>
#include <stdio.h>

int sd_mount_early_filesystems(void)
{
    int errors = 0;

    if (mount("proc", "/proc", "proc",
              MS_NOSUID | MS_NODEV | MS_NOEXEC, NULL) < 0
        && errno != EBUSY) {
        perror("systemd: mount /proc");
        errors++;
    }

    if (mount("sysfs", "/sys", "sysfs",
              MS_NOSUID | MS_NODEV | MS_NOEXEC, NULL) < 0
        && errno != EBUSY) {
        perror("systemd: mount /sys");
        errors++;
    }

    if (mount("devtmpfs", "/dev", "devtmpfs",
              MS_NOSUID, "mode=0755") < 0
        && errno != EBUSY) {
        perror("systemd: mount /dev");
        errors++;
    }

    if (mount("devpts", "/dev/pts", "devpts",
              MS_NOSUID | MS_NOEXEC,
              "mode=0620,ptmxmode=0666") < 0
        && errno != EBUSY) {
        perror("systemd: mount /dev/pts");
        errors++;
    }

    if (mount("tmpfs", "/dev/shm", "tmpfs",
              MS_NOSUID | MS_NODEV,
              "mode=1777") < 0
        && errno != EBUSY) {
        perror("systemd: mount /dev/shm");
        errors++;
    }

    return errors ? 1 : 0;
}
