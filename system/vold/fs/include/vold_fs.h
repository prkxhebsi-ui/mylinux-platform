#ifndef MYLINUX_VOLD_FS_H
#define MYLINUX_VOLD_FS_H

enum vold_fs_type {
    VOLD_FS_UNKNOWN = 0,
    VOLD_FS_EXT4,
    VOLD_FS_F2FS,
    VOLD_FS_VFAT
};

/*
 * Inspect an already-open file descriptor.
 * The descriptor is not closed, and the filesystem is not modified.
 * Returns VOLD_FS_UNKNOWN when the format cannot be identified.
 */
enum vold_fs_type vold_fs_detect_fd(int fd);

const char *vold_fs_name(enum vold_fs_type type);

#endif
