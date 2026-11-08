#ifndef MYLINUX_SYS_MOUNT_H
#define MYLINUX_SYS_MOUNT_H

/*
 * MyLinux Bionic-compatible mount interface.
 * Self-contained header; no external header imports.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Mount flags */
#define MS_RDONLY       1UL
#define MS_NOSUID       2UL
#define MS_NODEV        4UL
#define MS_NOEXEC       8UL
#define MS_SYNCHRONOUS  16UL
#define MS_REMOUNT      32UL
#define MS_MANDLOCK     64UL
#define MS_DIRSYNC      128UL
#define MS_NOSYMFOLLOW  256UL
#define MS_NOATIME      1024UL
#define MS_NODIRATIME   2048UL
#define MS_BIND         4096UL
#define MS_MOVE         8192UL
#define MS_REC          16384UL
#define MS_SILENT       32768UL
#define MS_POSIXACL     (1UL << 16)
#define MS_UNBINDABLE   (1UL << 17)
#define MS_PRIVATE      (1UL << 18)
#define MS_SLAVE        (1UL << 19)
#define MS_SHARED       (1UL << 20)
#define MS_RELATIME     (1UL << 21)
#define MS_KERNMOUNT    (1UL << 22)
#define MS_I_VERSION    (1UL << 23)
#define MS_STRICTATIME  (1UL << 24)
#define MS_LAZYTIME     (1UL << 25)

/* Unmount flags */
#define MNT_FORCE       1
#define MNT_DETACH      2
#define MNT_EXPIRE      4
#define UMOUNT_NOFOLLOW 8

/* Mount API */
int mount(
    const char *source,
    const char *target,
    const char *filesystemtype,
    unsigned long mountflags,
    const void *data
);

int umount(const char *target);

int umount2(const char *target, int flags);

#ifdef __cplusplus
}
#endif

#endif
